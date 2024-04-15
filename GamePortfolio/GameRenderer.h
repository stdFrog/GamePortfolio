#pragma once

class GameRenderer
{
    BOOL _bPerformInitialized = FALSE;
    BOOL _bEngineInitialized = FALSE;
    BOOL _bGDIInitialized = FALSE;
    BOOL _bDrawInitialized = FALSE;
    BOOL _bMappingReady = FALSE;

    long long _StartTimeStamp = 0;
    long long _FrameTimeStamp = 0;
    
    float _CyclesPerMilliSeconds = 0.f;
    float _PerformFrequency = 0.f;
    float _ElapsedTime = 0.f;
    float _FrameTime = 0.f;
    float _FrameFPS = 0.f;

private:
    HWND _hWnd;
    RECT _crt, _wrt;
    HDC _hDC, _hMemDC;
    // HANDLE _hMap;

    PVOID _pRaster;
    // LPVOID _pMap;
    HBITMAP _hOldBitmap, _hDIB;

private:
    BOOL GDIInitialize();
    BOOL PerformInitialize();
    void ReleaseGDI();
    void MemoryMapping();
    void DrawBitmap();

private:
    GameEngine _MainEngine;

public:
    GameEngine& GetGameEngine() { return _MainEngine; }
    const GameEngine& GetGameEngine() const { return _MainEngine; }

public:
    long long GetQuadPart();
    float GetPerMilliSeconds(BOOL bTrue = TRUE);
    float GetFrameFPS() const { return  _FrameFPS; }
    float GetElapsedTime() const { return _ElapsedTime; }

public:
    GameRenderer(HWND hWnd);
    ~GameRenderer();

    void Tick();
    void Render();
    void Update(float);
    void LoadScene();

public:
    void OnResize(WPARAM wParam, LPARAM lParam);
    void OnMapping();
};