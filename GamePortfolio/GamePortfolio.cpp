#include "pch.h"
#include "MainWindow.h"

HWND hWndMain;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nCmdShow) {
    MainWindow win;

    if (!win.Create(L"Game Portfolio")){
        return 0;
    }

    ShowWindow(win.Window(), nCmdShow);
    WindowsUtility::CenterWindow(win.Window());

    GameRenderer GRender(win.Window());
    win.SetMapNotify(&GRender, &GameRenderer::OnMapping);
    win.SetResizeNotify(&GRender, &GameRenderer::OnResize);

    static long long PreviousTime = 0;
    static float UpdatePeriod = 500.f;

    MSG msg = { 0 };
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }else{
            GRender.Tick();
            float CurrentTime = GRender.GetElapsedTime();
            
            if (CurrentTime - PreviousTime > UpdatePeriod){
                float FramePerSeconds = GRender.GetFrameFPS();
                WindowsUtility::SetWindowTitle(win.Window(), FramePerSeconds);
                PreviousTime = CurrentTime;
            }

        }
    }

    return (int)msg.wParam;
}