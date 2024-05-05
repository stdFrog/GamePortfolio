#pragma once
#include "Actor.h"

class Flipbook;

class FlipbookActor : public Actor
{
	using Super = Actor;

protected:
	Flipbook* _Flipbook;

protected:
	float _Time = 0.f;
	int _Index = 0;

public:
	void SetFlipbook(Flipbook*);
	void Reset();

public:
	FlipbookActor(ObjectType Type = ObjectType::None);
	virtual ~FlipbookActor();

	virtual BOOL Initialize();				// BeginPlay
	virtual void Update(float);				// Tick
	virtual void Render(HDC);
};

