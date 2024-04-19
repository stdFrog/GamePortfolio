#pragma once
#include <commdlg.h>
#define _SIZEOF(N) (sizeof(N)/sizeof(N[0]))
#define _TEXTOUT(DC, X, Y, TEXT) TextOut(DC, X, Y, TEXT, lstrlen(TEXT));

namespace WindowsUtility
{
	static void GetWindowSize(HWND hWnd, PLONG Width, PLONG Height) {
		RECT crt;

		GetClientRect(hWnd, &crt);
		*Width = crt.right - crt.left;
		*Height = crt.bottom - crt.top;
	}

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

	struct FileHeader {
		TCHAR szHeader[0x20];
		int Version;
	};

	static void* Open() {
		void* Buffer = NULL;
		OPENFILENAME OFN = {sizeof(OPENFILENAME), };
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

		if (!ReadFile(hFile, Buffer, dwFileSize, &dwRead, NULL)) {
			CloseHandle(hFile);
			return NULL;
		}

		CloseHandle(hFile);
		return Buffer;
	}

	static BOOL Write(const TCHAR* lpszFilePath, const TCHAR* format, ...) {
		va_list Mark;
		va_start(Mark, format);

		DWORD dwWritten;
		HANDLE hFile = CreateFile(lpszFilePath, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE) { return FALSE; }

		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			SetFilePointer(hFile, NULL, NULL, FILE_END);
		}

		TCHAR Buffer[0x400];
		_vstprintf_s(Buffer, _SIZEOF(Buffer), format, Mark);
		if (!WriteFile(hFile, Buffer, lstrlen(Buffer) * sizeof(TCHAR), &dwWritten, NULL)) {
			CloseHandle(hFile);
			return FALSE;
		}

		CloseHandle(hFile);
		va_end(Mark);
		return TRUE;
	}

	// Read(TEXT("DrawList.txt"), TEXT("%d"), &Count);
	// Read(TEXT("DrawList.txt"), TEXT("(%d,%d)->(%d,%d)"), &pt1.x, &pt1.y, &pt2.x, &pt2.y);

	static TCHAR* strchr(const TCHAR* String, const TCHAR Char) {
		while (*String) {
			if (*String == Char) { return (TCHAR*)String; }
			String++;
		}

		return NULL;
	}

	static int strcmp(const TCHAR* String, const TCHAR* Pattern) {
		TCHAR* L = (TCHAR*)String, * R = (TCHAR*)Pattern;

		int ret = 0;
		while (ret == 0 && *R) {
			ret = *L - *R;
			L++; R++;
		}

		int positive = (ret > 0);
		int negative = (ret < 0);

		if ((positive - negative) == 0) { return 0; }
		if ((positive - negative) > 0) { return -1; }
		if ((positive - negative) < 0) { return 1; }

		return -2147483648;
	}

	typedef struct tag_MapObject {
		HANDLE hFile;
		HANDLE hMap;
		TCHAR* Pointer;
	}MapView;

	static void CloseMapObject(MapView* DestroyTarget) {
		if (DestroyTarget->Pointer) {
			UnmapViewOfFile(DestroyTarget->Pointer);
		}

		if (DestroyTarget->hMap) {
			CloseHandle(DestroyTarget->hMap);
		}

		if (DestroyTarget->hFile) {
			CloseHandle(DestroyTarget->hFile);
		}

		free(DestroyTarget);
	}

	static MapView* GetPointer(const TCHAR* lpszFilePath) {
		if (lpszFilePath == NULL) { return FALSE; }

		MapView* ret = (MapView*)malloc(sizeof(MapView));

		ret->hFile = CreateFile(lpszFilePath, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (ret->hFile == INVALID_HANDLE_VALUE) { return FALSE; }

		// TODO : 읽어들일 정수형 개수 확인했고 문서 읽은 후 데이터 전달받아서 인자로 전달
		ret->hMap = CreateFileMapping(ret->hFile, NULL, PAGE_READONLY, 0, 0, NULL);
		ret->Pointer = (TCHAR*)MapViewOfFile(ret->hMap, FILE_MAP_READ, 0, 0, 0);

		return ret;
	}

	static void Read(MapView* Target, const TCHAR* format, ...) {
		if (Target == NULL) { return; }
		if (Target->hFile == INVALID_HANDLE_VALUE) { return; }
		
		va_list Mark;
		va_start(Mark, format);
		char* SetArguments = (char*)&format + sizeof(format);
		
		TCHAR* ptr = strchr(format, '%');
		const TCHAR* INTFORM = TEXT("%d");

		int Count = 0;
		while (*ptr) {
			if (strcmp(ptr, INTFORM)) {
				Count++;
			}
			ptr = strchr(ptr + 1, '%');
		}

		TCHAR* Front = Target->Pointer;
		for (Front; Count > 0 && *Front; Front++) {
			if (*Front < '0' || *Front > '9') { continue; }

			int ret = 0;
			TCHAR* Rear = Front;

			while (*Rear) {
				if (*Rear >= '0' && *Rear <= '9') {
					ret *= 10 + *Rear;
				}
				else {
					Count--;
					break;
				}
				Rear++;
			}

			*(*(int**)((SetArguments += sizeof(int*)) - sizeof(int*))) = ret;
		}

		va_end(Mark);
	}

	static BOOL SaveAs(const TCHAR* lpszFilePath, TCHAR* lpszContent) {
		OPENFILENAME OFN = { sizeof(OPENFILENAME), };
		TCHAR lpstrFile[MAX_PATH] = TEXT("");

		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.lpstrFile = lpstrFile;
		OFN.lpstrFilter = TEXT("Text File(*.txt)\0*.txt\0Every File(*.*)\0*.*\0\0");
		OFN.hwndOwner = HWND_DESKTOP;
		OFN.nMaxFile = MAX_PATH;
		OFN.lpstrDefExt = TEXT("txt");

		if (GetSaveFileName(&OFN) == 0) {
			return FALSE;
		}

		DWORD dwWritten;
		HANDLE hFile = CreateFile(lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE) { return FALSE; }

		if (!WriteFile(hFile, lpszContent, lstrlen(lpszContent) * sizeof(TCHAR), &dwWritten, NULL)){
			CloseHandle(hFile);
			return FALSE;
		}

		CloseHandle(hFile);
		return TRUE;
	}

	static void* LoadBmp(BITMAPINFOHEADER* ih)	{
		void* buf = NULL;
		TCHAR lpstrFile[MAX_PATH] = TEXT("");
		TCHAR FileName[MAX_PATH];
		TCHAR InitDir[MAX_PATH];
		TCHAR* path[MAX_PATH];
		TCHAR* pt = NULL;
		OPENFILENAME ofn;

		memset(&ofn, 0, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.lpstrFile = lpstrFile;
		ofn.lpstrFilter = TEXT("모든 파일(*.*)\0*.*\0비트맵 파일(*.bmp)\0*.bmp\0\0");
		ofn.lpstrTitle = TEXT("비트맵 파일을 선택하세요");
		ofn.lpstrDefExt = TEXT("txt");
		ofn.nMaxFile = MAX_PATH;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.hwndOwner = NULL;

		GetWindowsDirectory(InitDir, MAX_PATH);
		ofn.lpstrInitialDir = InitDir;

		if (GetOpenFileName(&ofn) != 0)
		{
			if (wcscmp(lpstrFile + ofn.nFileExtension, TEXT("bmp")) == 0)
			{
				HANDLE hFile = CreateFile(lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

				if (hFile != INVALID_HANDLE_VALUE)
				{
					DWORD dwRead;
					SetFilePointer(hFile, sizeof(BITMAPFILEHEADER), NULL, FILE_BEGIN);
					if (ReadFile(hFile, ih, sizeof(BITMAPINFOHEADER), &dwRead, NULL))
					{
						if (ih->biSizeImage == 0)
						{
							ih->biSizeImage = (((ih->biBitCount * ih->biWidth + 31) & ~31) >> 3) * ih->biHeight;
						}

						buf = malloc(ih->biSizeImage);
						if (ReadFile(hFile, buf, ih->biSizeImage, &dwRead, NULL))
						{
							CloseHandle(hFile);
							return buf;
						}
						else {
							Trace(TEXT("Failed to read bmp file data"));
						}
					}
					else {
						Trace(TEXT("Failed to ReadFile"));
					}
					CloseHandle(hFile);
				}
				else {
					Trace(TEXT("cannot open this file"));
				}
			}
			else {
				Trace(TEXT("those not bmp file"));
			}
		}

		return NULL;
	}
}

