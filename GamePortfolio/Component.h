#pragma once

class Component
{
protected:
	Actor* _Owner;

public:
	virtual BOOL Initialize() { return TRUE; }
	virtual void Update(float) {}
	virtual void Render(HDC) {}

public:
	void SetOwner(Actor* Owner) { _Owner = Owner; }
	Actor* GetOwner() { return _Owner; }

public:
	Component();
	virtual ~Component();
};

