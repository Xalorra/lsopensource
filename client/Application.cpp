#include "stdafx.h"
#include "Application.h"
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#define APPLICATION_NAME "Lost Saga Offline"
#define WINDOW_STYLE (WS_OVERLAPPED | WS_CAPTION | WS_CLIPCHILDREN)
#define FULLSCREEN_STYLE (WS_POPUP | WS_CLIPCHILDREN)

template<> Application* Singleton< Application >::ms_Singleton = 0;

Application& Application::GetSingleton()
{
	return Singleton< Application >::GetSingleton();
}


Application::Application()
{
	m_hInstance = NULL;
	m_hWnd = NULL;

	m_iWidth = 0;
	m_iHeight = 0;
	m_iDeskTopWidth = 0;
	m_iDeskTopHeight = 0;

	isFullScreen = false;
}

Application::~Application()
{
}

bool Application::OnNCPaint(HDC hDC)
{
	if (!m_hWindowTitleLosa || !m_hWindowOutLine)
		return false;

	RECT rcWindow;
	GetWindowRect(m_hWnd, &rcWindow);

	int iWidth = rcWindow.right - rcWindow.left;
	int iHeight = rcWindow.bottom - rcWindow.top;

	HDC hBitmapDC = CreateCompatibleDC(hDC);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hBitmapDC, m_hWindowTitleLosa);

	// top ( 이미지 하나를 삼등분해서 사용한다 )

	enum { FRONT_WIDTH = 173, HEIGHT = 29, };
	StretchBlt(hDC, 0, 0, FRONT_WIDTH, HEIGHT, hBitmapDC, 0, 0, FRONT_WIDTH, HEIGHT, SRCCOPY); // title front

	enum { X_START = 173, CENTER_WIDTH = 8, END_WIDTH = 11 };
	int iTopCenterWidth = iWidth - FRONT_WIDTH + END_WIDTH;  // title center
	StretchBlt(hDC, FRONT_WIDTH, 0, iTopCenterWidth, HEIGHT, hBitmapDC, X_START, 0, CENTER_WIDTH, HEIGHT, SRCCOPY);

	int iTopRightStart = iWidth - END_WIDTH;
	StretchBlt(hDC, iTopRightStart, 0, END_WIDTH, HEIGHT, hBitmapDC, X_START, 0, END_WIDTH, HEIGHT, SRCCOPY); // title end

	// left & right
	SelectObject(hBitmapDC, m_hWindowOutLine);

	int iSideHeight = iHeight - 29 - 3;
	StretchBlt(hDC, 0, 29, 3, iSideHeight, hBitmapDC, 0, 0, 3, 3, SRCCOPY);

	int iSideRightStart = iWidth - 3;
	StretchBlt(hDC, iSideRightStart, 29, 3, iSideHeight, hBitmapDC, 3 * 2, 0, 3, 3, SRCCOPY);

	// bottom
	int iBottomStart = iHeight - 3;
	StretchBlt(hDC, 0, iBottomStart, 3, 3, hBitmapDC, 0, 3, 3, 3, SRCCOPY);

	int iBottomCenterWidth = iWidth - 3 * 2;
	StretchBlt(hDC, 3, iBottomStart, iBottomCenterWidth, 3, hBitmapDC, 3, 3, 3, 3, SRCCOPY);

	int iBottomRightStart = iWidth - 3;
	StretchBlt(hDC, iBottomRightStart, iBottomStart, 3, 3, hBitmapDC, 3 * 2, 3, 3, 3, SRCCOPY);

	SelectObject(hBitmapDC, hOldBitmap);
	DeleteDC(hBitmapDC);

	return true;
}

LRESULT Application::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg)
	{
	case WM_NCPAINT:
	case WM_NCACTIVATE:
	{
		bool bPaintOK = false;

		HDC hDC = GetWindowDC(hWnd);
		if (hDC)
		{
			SetWindowRgn(hWnd, NULL, FALSE);
			bPaintOK = OnNCPaint(hDC);
			ReleaseDC(hWnd, hDC);
		}

		if (bPaintOK)
		{
			if (uMsg == WM_NCPAINT)
				return 0;

			if (uMsg == WM_NCACTIVATE)
				return TRUE;
		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return NULL;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return g_App.MsgProc(hWnd, uMsg, wParam, lParam);
}

bool Application::InitializeWindow(HINSTANCE hInstance) {

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APPLICATION_NAME;
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	RegisterClassEx(&wc);

	HWND hWnd;
	hWnd = CreateWindowEx(0,
		APPLICATION_NAME,
		APPLICATION_NAME,
		WINDOW_STYLE,
		0, 0, 0, 0,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (FAILED(hWnd))
		return false;

	m_hWnd = hWnd;
	m_hInstance = hInstance;

	m_iWidth = 0;
	m_iHeight = 0;
	m_iDeskTopWidth = GetSystemMetrics(SM_CXSCREEN);
	m_iDeskTopHeight = GetSystemMetrics(SM_CYSCREEN);

	DWORD dwIDTitleBmp = IDB_WINDOW_TITLE_LOSA;

	m_hWindowTitleLosa = LoadBitmap(hInstance, MAKEINTRESOURCE(dwIDTitleBmp));
	m_hWindowOutLine = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_WEB_OUTLINE));

	return true;
}

int Application::Run()
{

	ModifyMainWindow();

	MSG msg;

	
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, NULL, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}


void Application::ModifyMainWindow()
{
	m_iWidth = max(0, 800);
	m_iHeight = max(0, 600);
	
	if (!isFullScreen)
	{
		SetWindowLong(m_hWnd, GWL_STYLE, WINDOW_STYLE);
		SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOREDRAW | SWP_NOSIZE);

		RECT rcRect;
		SetRect(&rcRect, 0, 0, m_iWidth, m_iHeight);
		AdjustWindowRectEx(&rcRect, WINDOW_STYLE, FALSE, 0);

		MoveWindow(m_hWnd,
			(m_iDeskTopWidth - m_iWidth) / 2 - 3,
			(m_iDeskTopHeight - m_iHeight) / 2 - 22,
			rcRect.right - rcRect.left,
			rcRect.bottom - rcRect.top,
			FALSE);
	}
	else
	{
		// 최초에 FULLSCREEN_STYLE로 만들었으므로 SetWindowLong 안함
		MoveWindow(m_hWnd, 0, 0, m_iWidth, m_iHeight, FALSE);
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}

bool Application::InitializeResource()
{
	char szRootDir[MAX_PATH];
	char szFullPath[MAX_PATH] = "";
	::GetCurrentDirectory(MAX_PATH, szRootDir);


#ifdef USE_PACK
	g_ResourceLoader.Initialize(true);

	memset(szFullPath, 0, sizeof(szFullPath));
	StringCbPrintf(szFullPath, sizeof(szFullPath), "%s\\rs.iop", szRootDir);

	if (!g_ResourceLoader.AddPackFile(szFullPath, ""))
		return false;

	memset(szFullPath, 0, sizeof(szFullPath));
	StringCbPrintf(szFullPath, sizeof(szFullPath), "%s\\map.iop", szRootDir);

	if (!g_ResourceLoader.AddPackFile(szFullPath, "_map"))
		return false;

#else

	g_ResourceLoader.Initialize(false);

#endif

	return true;
}

