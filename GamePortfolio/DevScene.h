#pragma once

class DevScene : public BaseScene
{
	HWND _hWnd;
	LONG iWidth, iHeight;

public:
	DevScene();
	virtual ~DevScene();

public:
	virtual void Update(float);
	virtual void Render(HDC);
	virtual BOOL Initialize();
};

