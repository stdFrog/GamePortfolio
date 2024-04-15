#pragma once

template <class DERIVED_TYPE>
class BaseWindow {
public:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        DERIVED_TYPE* pThis = NULL;

        if (WM_NCCREATE == uMsg)
        {
            CREATESTRUCT* pCS = (CREATESTRUCT*)lParam;
            pThis = (DERIVED_TYPE*)pCS->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
            pThis->_hWnd = hWnd;
        }
        else {
            pThis = (DERIVED_TYPE*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        }

        if (pThis)
        {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        else {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }

    HWND Window() const { return _hWnd; }

    BOOL Create(
        LPCWSTR lpWindowName,
        DWORD dwStyle = WS_OVERLAPPEDWINDOW,
        DWORD dwStyleEx = 0,
        LONG x = CW_USEDEFAULT,
        LONG y = CW_USEDEFAULT,
        LONG Width = CW_USEDEFAULT,
        LONG Height = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    )
    {
        WNDCLASSEX wcex = {
                sizeof(wcex),
                CS_HREDRAW | CS_VREDRAW,
                DERIVED_TYPE::WndProc,
                0,0,
                GetModuleHandle(NULL),
                NULL, LoadCursor(NULL, IDC_ARROW),
                (HBRUSH)(COLOR_WINDOW + 1),
                NULL,
                ClassName(),
                NULL
        };

        RegisterClassEx(&wcex);

        _hWnd = CreateWindowEx(
            dwStyleEx,
            ClassName(),
            lpWindowName,
            dwStyle,
            x, y, Width, Height,
            hWndParent,
            hMenu,
            GetModuleHandle(NULL),
            this
        );

        return ((_hWnd) ? TRUE : FALSE);
    }

protected:
    HWND _hWnd = NULL;

    virtual LPCWSTR ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};