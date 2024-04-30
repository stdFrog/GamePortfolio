#pragma once
#include "Collider.h"

class RectCollider :public Collider
{
	using Super = Collider;
	Vector _Size;

public:
	Vector GetSize() { return _Size; }
	void SetSize(Vector Size) { _Size = Size; }

public:
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
	virtual BOOL CheckCollision(Collider* Other);

public:
	RectCollider();
	virtual ~RectCollider();
};