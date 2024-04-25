#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
	using Super = Collider;

private:
	float _Radius = 0.f;

public:
	float GetRadius() { return _Radius; }
	void SetRadius(float Radius) { _Radius = Radius; }

public:
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
	virtual BOOL CheckCollision(Collider* Other);

public:
	CircleCollider();
	virtual ~CircleCollider();
};