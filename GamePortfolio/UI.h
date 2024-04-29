#pragma once

class BaseScene;

class UI
{
protected:
	BaseScene* _Owner = NULL;

	Vector _Position = { 400, 300 };
	Vector _Size = { 150, 150 };

public:
	void SetPosition(Vector Position) { _Position = Position; }
	Vector GetPosition() { return _Position; }

public:
	BaseScene* GetOwner() { return _Owner; }
	void SetOwner(BaseScene* Owner) { _Owner = Owner; }

public:
	RECT GetRect();
	BOOL IsMouseInRect();

public:
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);

public:
	UI(BaseScene* CurrentScene = NULL);
	virtual ~UI();
};

