#pragma once
#include "FlipbookActor.h"

// 여기부터 컨텐츠 코드
class Player : public FlipbookActor
{
	using Super = FlipbookActor;

	Flipbook* _FlipbookUp = NULL;
	Flipbook* _FlipbookDown = NULL;
	Flipbook* _FlipbookLeft = NULL;
	Flipbook* _FlipbookRight = NULL;

public:
	Player();
	virtual ~Player();

	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};

