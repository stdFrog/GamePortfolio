#pragma once

class UI
{
protected:
	Panel* _Owner = NULL;

	Vector _Position = { 400, 300 };
	Vector _Size = { 150, 150 };

public:
	Panel* GetOwner() { return _Owner; }
	void SetOwner(Panel* Owner) { _Owner = Owner; }

public:
	void SetPosition(Vector Position) { _Position = Position; }
	Vector GetPosition() { return _Position; }

public:
	RECT GetRect();
	BOOL IsMouseInRect();

public:
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);

public:
	UI();
	virtual ~UI();
};