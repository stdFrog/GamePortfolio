#pragma once
#include "SpriteActor.h"

// 여기부터 컨텐츠 코드
class Player : public SpriteActor
{
	using Super = SpriteActor;

public:
	Player();
	virtual ~Player();

	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};

