#pragma once
#include "Component.h"

class Sprite;

class SpriteRenderer : public Component
{
	Sprite* _Sprite = NULL;

public:
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);

	void SetSprite(Sprite* sprite) { _Sprite = sprite; }
};

