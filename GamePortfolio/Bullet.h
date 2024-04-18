#pragma once
#include "ObjectInterface.h"

class Bullet :public ObjectInterface
{
	Vector _Speed;

public:
	void SetSpeed(Vector Speed) { _Speed = Speed; }

public:
	Bullet();
	virtual ~Bullet();

	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};