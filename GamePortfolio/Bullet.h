#pragma once
#include "ObjectInterface.h"

class Bullet :public ObjectInterface
{
	Vector _Speed;
	ObjectInterface* _Owner = NULL;				// 나 자신을 피격하지 않도록

public:
	void SetSpeed(Vector Speed) { _Speed = Speed; }
	Vector GetSpeed() { return _Speed; }

	ObjectInterface* GetOwner() { return _Owner; }
	void SetOwner(ObjectInterface* Owner) { _Owner = Owner; }

public:
	Bullet();
	virtual ~Bullet();

	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};