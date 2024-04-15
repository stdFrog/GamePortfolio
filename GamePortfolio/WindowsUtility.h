#pragma once
#include <commdlg.h>
#define _SIZEOF(N) (sizeof(N)/sizeof(N[0]))
#define _TEXTOUT(DC, X, Y, TEXT) TextOut(DC, X, Y, TEXT, lstrlen(TEXT));

namespace WindowsUtility
{
	static void SetWindowTitle(HWND hWnd, float FPS) {
		TCHAR str[128];
		_stprintf_s(str, TEXT("[%.4f fps]"), FPS);
		SetWindowText(hWnd, str);
	}

	static void CenterWindow(HWND hWnd) {
		RECT wrt, srt;
		LONG lWidth, lHeight;
		POINT NewPosition;

		GetWindowRect(hWnd, &wrt);
		GetWindowRect(GetDesktopWindow(), &srt);

		lWidth = wrt.right - wrt.left;
		lHeight = wrt.bottom - wrt.top;
		NewPosition.x = (srt.right - lWidth) / 2;
		NewPosition.y = (srt.bottom - lHeight) / 2;

		SetWindowPos(hWnd, NULL, NewPosition.x, NewPosition.y, lWidth, lHeight, SWP_NOZORDER);
	}

	static void Trace(LPCTSTR format, ...) {
		TCHAR Buffer[0x400];

		va_list Mark;
		va_start(Mark, format);

		_vstprintf_s(Buffer, _SIZEOF(Buffer), format, Mark);
		lstrcat(Buffer, L"\r\n");

		OutputDebugString(Buffer);
		va_end(Mark);
	}

	static void WriteLog(LPCTSTR format, ...) {
		va_list Mark;
		va_start(Mark, format);

		static int Count = 0;
		static LPTSTR LogPath = NULL;

		GetCurrentDirectory(_SIZEOF(LogPath), LogPath);
		lstrcat(LogPath, L"\r\n");

		TCHAR lpszLog[0x400], lpszLog2[0x400];
		_vstprintf_s(lpszLog, _SIZEOF(lpszLog), format, Mark);

		HANDLE hFile = NULL;
		if (Count == 0) {
			hFile = CreateFile(LogPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		}
		else {
			hFile = CreateFile(LogPath, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		}

		SYSTEMTIME st;
		GetLocalTime(&st);

		_stprintf_s(lpszLog2, _SIZEOF(lpszLog2), TEXT("%06d - {%d : %d : %d : %d} %s\r\n"), Count++, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, lpszLog);
		SetFilePointer(hFile, NULL, NULL, FILE_END);

		DWORD dwWritten;
		WriteFile(hFile, lpszLog2, lstrlen(lpszLog2), &dwWritten, NULL);
		CloseHandle(hFile);

		va_end(Mark);
	}

	static  void DrawRect(HDC hdc, Vector Origin, int iWidth, int iHeight) {
		int Ox = (int)Origin.x, Oy = (int)Origin.y;
		int W = (int)iWidth / 2, H = (int)iHeight / 2;

		Rectangle(hdc, Ox - W, Oy - H, Ox + W, Oy + H);
	}

	static void DrawCircle(HDC hdc, Vector Origin, int iRadius) {
		int Ox = (int)Origin.x, Oy = (int)Origin.y;

		Ellipse(hdc, Ox - iRadius, Oy - iRadius, Ox + iRadius, Oy + iRadius);
	}

	static void DrawLine(HDC hdc, Vector From, Vector To) {
		int Fx = (int)From.x, Fy = (int)From.y;
		int Tx = (int)To.x, Ty = (int)To.y;

		MoveToEx(hdc, Fx, Fy, NULL);
		LineTo(hdc, Tx, Ty);
	}

	static void* Open() {
		void* Buffer = NULL;
		OPENFILENAME OFN = {sizeof(OFN),};
		TCHAR lpstrFile[MAX_PATH] = TEXT("");
		
		OFN.lpstrFile = lpstrFile;
		OFN.lpstrFilter = TEXT("TextFile(*.txt)\0*.txt\0Every File(*.*)\0*.*\0\0");
		OFN.hwndOwner = HWND_DESKTOP;
		OFN.nMaxFile = MAX_PATH;
		OFN.lpstrDefExt = TEXT("txt");

		if (GetOpenFileName(&OFN) == 0) { return NULL; }

		DWORD dwRead;
		HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE) { return NULL; }

		DWORD dwFileSize = GetFileSize(hFile, NULL);
		if (Buffer == NULL) {
			Buffer = (void*)malloc(dwFileSize);
		}

		ReadFile(hFile, Buffer, dwFileSize, &dwRead, NULL);
		CloseHandle(hFile);

		return Buffer;
	}
}

