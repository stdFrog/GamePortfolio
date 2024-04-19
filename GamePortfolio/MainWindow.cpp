#include "pch.h"
#include "MainWindow.h"

MainWindow::MainWindow() : _hTimer(NULL), _Class(NULL), ResizeNotify(NULL) {

}

MainWindow::~MainWindow() {
    if (_lpFileHeader) { UnmapViewOfFile(_lpFileHeader); }
    if (_hFileMap) { CloseHandle(_hFileMap); }
    if (_hTimer) { CloseHandle(_hTimer); }
}

BOOL MainWindow::InitializeTimer() {
    _hTimer = CreateWaitableTimer(NULL, FALSE, NULL);

    if (_hTimer == NULL) {
        return FALSE;
    }

    LARGE_INTEGER li = { 0 };
    if (!SetWaitableTimer(_hTimer, &li, (1000 / 60), NULL, NULL, FALSE)) {
        CloseHandle(_hTimer);
        _hTimer = NULL;
        return FALSE;
    }

    return TRUE;
}

BOOL MainWindow::CreateMapping() {
    /*
    TCHAR szClass[256];

    WindowsUtility::Traceback(TEXT("Activate App"));
    if (GetClassName(_hWnd, szClass, 256) != 0) {
        WindowsUtility::Traceback(TEXT("Search ClassName"));
        if (lstrcmp(szClass, ClassName()) == 0) {
            WindowsUtility::Traceback(TEXT("Find ClassName"));
            size_t Shared = sizeof(TCHAR) * (lstrlen(ClassName()) + 1);
            _hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, (DWORD)Shared, TEXT("INHERITWINDOWHANDLE"));
            if (_hFileMap == NULL) {
                WindowsUtility::Traceback(TEXT("Mapping Is Invalid"));
                return FALSE;
            }
            _lpFileHeader = (TCHAR*)MapViewOfFile(_hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, Shared);
            if (_lpFileHeader == NULL) {
                WindowsUtility::Traceback(TEXT("FileHeader Is Invalid"));
                if (_hFileMap) { CloseHandle(_hFileMap); }
                return FALSE;
            }

            lstrcpy((TCHAR*)_lpFileHeader, ClassName());
            WindowsUtility::Traceback(TEXT("Create FileMap"));
        }
    }

    */
    return TRUE;
}


void MainWindow::WaitTimer() {
    if (MsgWaitForMultipleObjects(1, &_hTimer, FALSE, INFINITE, QS_ALLINPUT) == WAIT_OBJECT_0) {
        InvalidateRect(_hWnd, NULL, FALSE);
    }
}

LRESULT MainWindow::HandleMessage(UINT iMessage, WPARAM wParam, LPARAM lParam) {
    DWORD i;

    for (i = 0; i < sizeof(MainMsg) / sizeof(MainMsg[0]); i++) {
        if (MainMsg[i].iMessage == iMessage) {
            return (this->*MainMsg[i].lpfnWndProc)(wParam, lParam);
        }
    }

    return DefWindowProc(_hWnd, iMessage, wParam, lParam);
}

LRESULT MainWindow::OnCreate(WPARAM wParam, LPARAM lParam) {
    if (!InitializeTimer() || !CreateMapping()) {
        return -1;
    }

    DWORD dwStyle = GetWindowLong(this->Window(), GWL_STYLE);
    SetWindowLong(this->Window(), GWL_STYLE, dwStyle & ~WS_THICKFRAME);
    SendMessage(this->Window(), WM_NCPAINT, 1, 0);

    // SetTimer(_hWnd, 1, 1000, NULL);

    return 0;
}

LRESULT MainWindow::OnDestroy(WPARAM wParam, LPARAM lParam) {
    // KillTimer(_hWnd, 1);
    PostQuitMessage(0);
    return 0;
}

LRESULT MainWindow::OnSize(WPARAM wParam, LPARAM lParam) {
    if (wParam != SIZE_MINIMIZED) {
        if (_Class && ResizeNotify) {
            ((GameRenderer*)_Class->*ResizeNotify)(wParam, lParam);
        }
    }

    return 0;
}

/*
LRESULT MainWindow::OnExitResizeMove(WPARAM wParam, LPARAM lParam) {
    if (wParam != SIZE_MINIMIZED) {
        if (_Class && ResizeNotify) {
            ((GameRenderer*)_Class->*ResizeNotify)(wParam, lParam);
        }
    }

    return 0;
}
*/

LRESULT MainWindow::OnPaint(WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    BeginPaint(_hWnd, &ps);
    EndPaint(_hWnd, &ps);
    return 0;
}

LRESULT MainWindow::OnTimer(WPARAM wParam, LPARAM lParam) {
    /*
    switch (wParam) {
    case 1:
        KillTimer(_hWnd, 1);
        if (_Class && MapNotify) {
            WindowsUtility::Traceback(TEXT("Call MapNotify"));
            ((GameRenderer*)_Class->*MapNotify)();
        }
        break;
    }
    */
    return 0;
}