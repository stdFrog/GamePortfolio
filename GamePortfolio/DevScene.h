#pragma once

class Actor;
class GameObject;

class DevScene : public BaseScene
{
	// BaseScene에서 관리하는 Object에 추가할 것인지,
	// DevScene에서 따로 관리할 것인지 고민해볼 것
	std::vector<Actor*> _Actors;

	HWND _hWnd;
	LONG iWidth, iHeight;

public:
	DevScene();
	virtual ~DevScene();

public:
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};

