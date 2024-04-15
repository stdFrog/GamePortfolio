#include "pch.h"
#include "GameRenderer.h"

GameRenderer::GameRenderer(HWND hWnd) :
	_hWnd(hWnd), _crt({ 0,0,0,0 }), _wrt({ 0, 0, 0, 0 }),
	_hDC(NULL), _hMemDC(NULL), _hMap(NULL), _pMap(NULL),
	_pRaster(NULL), _hOldBitmap(NULL), _hDIB(NULL), _MainEngine()
{
	
}

GameRenderer::~GameRenderer() {
	if (_pMap) { UnmapViewOfFile(_pMap); }
	if (_hMap) { CloseHandle(_hMap); }
	ReleaseGDI();
	// _CrtDumpMemoryLeaks();
}

void GameRenderer::OnMapping() {
	// _bMappingReady = TRUE;
}

void GameRenderer::OnResize(WPARAM wParam, LPARAM lParam) {
	ReleaseGDI();
}

void GameRenderer::Tick() {
	/*
	if (_bMappingReady) {
		MemoryMapping();
	}
	*/
	// GameEngine, Input, Perform, Scene;
	if (!_bPerformInitialized) {
		_bPerformInitialized = PerformInitialize();
	}

	// Possibility that it will be terminated due to an unknown error
	_bEngineInitialized = GetGameEngine().IsInitialized();
	if (!_bEngineInitialized) {
		_bEngineInitialized = GetGameEngine().Initialize(_hWnd);
	}

	if (!_bGDIInitialized) {
		_bGDIInitialized = GDIInitialize();
	}

	// Double Check
	if (!_bPerformInitialized || !_bEngineInitialized || !_bGDIInitialized) { return; }

	// Player Input - Logic - Rendering – Present
	_FrameTimeStamp = GetQuadPart();											// 렌더링 전 시간 확인
	_MainEngine.GetInputManager().Update();										// 사용자 입력 확인

	// DISPLAY - Variable Frame Rate											// 물리 법칙 추가할 일 없으면 추후 고정 비율로 변경
	Update(_FrameTime * 0.001f);												// 실행 (dtSeconds - unit : S)
	Render();																	// 그리기

	// PERFORMANCE
	INT64 CurrentTimeStamp = GetQuadPart();										// 렌더링 후 시간 확인
	INT64 FrameCycles = CurrentTimeStamp - _FrameTimeStamp;
	INT64 ElapsedCycles = CurrentTimeStamp - _StartTimeStamp;

	_ElapsedTime = ElapsedCycles / _CyclesPerMilliSeconds;						// 프로그램 실행 후 누적 경과 시간(unit : MS)
	_FrameTime = FrameCycles / _CyclesPerMilliSeconds;							// 한 컷당 소요 시간(unit : MS)
	_FrameFPS = ((_FrameTime == 0.f) ? 0.f : 1000.f) / _FrameTime;				// 초당 교체되는 화면의 수
}

void GameRenderer::LoadScene() {

}

void GameRenderer::Update(float dtSeconds) {
	if (!_bEngineInitialized) { return; }
	// TODO :

	auto& Engine = GetGameEngine();
	Engine.Update(dtSeconds);
	// Create GameObject, Player, Environment, ETC...
}

void GameRenderer::Render() {
	if (!_bGDIInitialized) { return; }
	SetBkMode(_hMemDC, TRANSPARENT);
	FillRect(_hMemDC, &_crt, GetSysColorBrush(COLOR_WINDOW));

	// TODO : Display Something
	auto& Engine = GetGameEngine();
	Engine.Render(_hMemDC);
	// TODO : Each component of the scene calls the required function.
	// 그리기 순서를 알기 쉽게 구성한다.

	// Flush
	DrawBitmap();
}

BOOL GameRenderer::PerformInitialize() {
	_PerformFrequency = GetPerMilliSeconds(FALSE);
	_CyclesPerMilliSeconds = _PerformFrequency / 1000.f;
	_StartTimeStamp = GetQuadPart();

	if (_CyclesPerMilliSeconds == 0.f || _StartTimeStamp == 0) {
		return FALSE;
	}

	return TRUE;
}


long long GameRenderer::GetQuadPart() {
	LARGE_INTEGER CurrentTime;

	if (!QueryPerformanceCounter(&CurrentTime)) {
		return 0;
	}

	return CurrentTime.QuadPart;
}

float GameRenderer::GetPerMilliSeconds(BOOL bTrue) {
	LARGE_INTEGER Frequency;

	if (!QueryPerformanceFrequency(&Frequency)) {
		return 0.f;
	}

	return ((bTrue) ? (float)(Frequency.QuadPart / 1000.f) : (float)(Frequency.QuadPart));
}

BOOL GameRenderer::GDIInitialize() {
	_hDC = GetDC(_hWnd);
	_hMemDC = CreateCompatibleDC(_hDC);

	if (_hDIB == NULL) {
		GetClientRect(_hWnd, &_crt);

		BITMAPINFO bmi = { 0 };
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = _crt.right - _crt.left;
		bmi.bmiHeader.biHeight = _crt.bottom - _crt.top;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biBitCount = GetDeviceCaps(_hDC, BITSPIXEL);

		_hDIB = CreateDIBSection(_hMemDC, &bmi, DIB_RGB_COLORS, (void**)&_pRaster, NULL, 0);
	}

	_hOldBitmap = (HBITMAP)SelectObject(_hMemDC, _hDIB);
	DeleteObject(_hOldBitmap);

	return (((_hDIB) && (_pRaster)) ? TRUE : FALSE);
}

void GameRenderer::ReleaseGDI() {
	if (!_bGDIInitialized) { return; }
	DeleteObject(_hOldBitmap);
	DeleteObject(_hDIB);
	DeleteDC(_hMemDC);
	ReleaseDC(_hWnd, _hDC);

	_hDIB = NULL;
	_bGDIInitialized = FALSE;
}

void GameRenderer::MemoryMapping() {
	/*
	if (_pMap) { UnmapViewOfFile(_pMap); }
	if (_hMap) { CloseHandle(_hMap); }

	WindowsUtility::Traceback(TEXT("Callback Recieve OnMapping Function"));
	_hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, TEXT("INHERITWINDOWHANDLE"));
	if (_hMap == NULL) {
		WindowsUtility::Traceback(TEXT("OpenFileMapping Failed"));
		return;
	}

	_pMap = (TCHAR*)MapViewOfFile(_hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (_pMap == NULL) {
		WindowsUtility::Traceback(TEXT("MapViewOfFile Failed"));
		return;
	}
	WindowsUtility::Traceback(TEXT("OpenFIleMapView Succeeded"));
	_hWnd = FindWindowEx(NULL, NULL, (TCHAR*)_pMap, NULL);

	_bMappingReady = FALSE;
	*/
}

void GameRenderer::DrawBitmap() {
	BITMAP bmp;
	GetObject(_hDIB, sizeof(BITMAP), &bmp);

	BitBlt(_hDC, 0, 0, bmp.bmWidth, bmp.bmHeight, _hMemDC, 0, 0, SRCCOPY);
}