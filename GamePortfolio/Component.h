#pragma once

class Component
{
public:
	virtual BOOL Initialize() {}
	virtual void Update(float) {}
	virtual void Render(HDC) {}

	// Owner
	// GameObject * _Owner;
};

