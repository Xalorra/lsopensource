#pragma once
class Application : public Singleton< Application >
{
protected:
	HINSTANCE		m_hInstance;
	HWND			m_hWnd;

	HBITMAP			m_hWindowTitleLosa;
	HBITMAP			m_hWindowOutLine;

	int				m_iWidth;
	int				m_iHeight;

	int				m_iDeskTopWidth;
	int				m_iDeskTopHeight;

	bool isFullScreen;
public:
	bool OnNCPaint(HDC hDC);
	LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	int Run();
	void ModifyMainWindow();

public:
	bool InitializeWindow(HINSTANCE hInstance);
	HWND GetHWnd() const { return m_hWnd; }
	bool InitializeResource();

public:
	static Application& GetSingleton();

public:
	Application();
	virtual ~Application();

};

#define g_App Application::GetSingleton()