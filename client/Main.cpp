#include "stdafx.h"
#include "resource.h"
#include <io.h>
#include "Application.h"


bool ProcessOptions();

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)
{

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (0 == access("log/game.log", 0))
    {
        if (!SetFileAttributes("log/game.log", FILE_ATTRIBUTE_NORMAL))
            return 0;
    }
    LOG.OpenLog(0, "log/game.log");


    LOG.PrintTimeAndLog(0, "[Main] - LostSaga Start");

    Application* pApp = new Application;

    LOG.PrintTimeAndLog(0, "[Main] - Process Option Start");

    if (!pApp->InitializeResource()) {
        return 0;
    }
	LOG.PrintTimeAndLog(0, "[Main] - Process Option Start Complete");



	int iRet = -1;

    if (pApp->InitializeWindow(hInstance)) {
		iRet = pApp->Run();
    }

	if (iRet == -1)
	{
		DestroyWindow(pApp->GetHWnd());

		MSG msg;
		for (int i = 0; i < 10000; i++)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				if (!GetMessage(&msg, NULL, 0, 0))
					break;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
				continue;
			}
			::SleepEx(1, FALSE);
		}
	}

    return iRet;
}


bool ProcessOptions()
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