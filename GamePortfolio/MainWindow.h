#pragma once
#include "GamePortfolio.h"

class MainWindow : public BaseWindow<MainWindow>
{
    static const int _nMsg = 1000;

    typedef struct tag_MSGMAP {
        UINT iMessage;
        LRESULT(MainWindow::* lpfnWndProc)(WPARAM, LPARAM);
    }MSGMAP;

    // QUERYENDSESSION
    MSGMAP MainMsg[_nMsg] = {
        {WM_TIMER, &MainWindow::OnTimer},
        {WM_PAINT, &MainWindow::OnPaint},
        {WM_DISPLAYCHANGE, &MainWindow::OnPaint},
        {WM_SIZE, &MainWindow::OnSize},
        // {WM_EXITSIZEMOVE, &MainWindow::OnExitResizeMove},
        {WM_CREATE, &MainWindow::OnCreate},
        {WM_DESTROY, &MainWindow::OnDestroy},
    };

private:
    HANDLE _hTimer;
    HANDLE _hFileMap;
    LPVOID _lpFileHeader;
    BOOL InitializeTimer();
    BOOL CreateMapping();

    PCWSTR ClassName() const { return L"Windows Api Game Portfolio"; }
    LRESULT OnTimer(WPARAM wParam, LPARAM lParam);
    LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
    LRESULT OnSize(WPARAM wParam, LPARAM lParam);
    LRESULT OnCreate(WPARAM wParam, LPARAM lParam);
    LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
    // LRESULT OnExitResizeMove(WPARAM wParam, LPARAM lParam);
    
private:
    void* _Class;
    void (GameRenderer::* MapNotify)();
    void (GameRenderer::* ResizeNotify)(WPARAM, LPARAM);

public:
    MainWindow();
    ~MainWindow();

    void WaitTimer();
    void SetMapNotify(void* Class, void(GameRenderer::* Send)()) { _Class = Class; MapNotify = Send; }
    void SetResizeNotify(void* Class, void(GameRenderer::* Send)(WPARAM, LPARAM)) { _Class = Class; ResizeNotify = Send; }
    LRESULT HandleMessage(UINT iMessage, WPARAM wParam, LPARAM lParam);
};

