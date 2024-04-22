#pragma once
#include "Actor.h"

// 엔진측 코드
class Sprite;

class SpriteActor : public Actor
{
	using Super = Actor;

protected:
	Sprite* _Sprite = NULL;

public:
	void SetSprite(Sprite* sprite) { _Sprite = sprite; }
	Sprite* GetSprite() { return _Sprite; }

public:
	SpriteActor(ObjectType Type = ObjectType::None);
	virtual ~SpriteActor();

	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};

