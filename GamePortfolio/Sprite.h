#pragma once
#include "ResourceBase.h"

// 상용 엔진에서는 Sprite라는 개념을 추가하여 좀 더 세분화시켰다.
// 텍스처를 조금 더 잘라내서 사용하고 싶을 때 만들어 사용하면 된다.
// 굳이 필요없으면 만들 필요 없다.
class Texture;

class Sprite :public ResourceBase
{
	int _x, _y, _cx, _cy;
	HDC _hDC;
	Texture* _Texture = NULL;


public:
	int GetTransparent();
	HDC GetSpriteDC();
	Vector GetPosition() { return Vector(static_cast<float>(_x), static_cast<float>(_y)); }
	Vector GetSize() { return Vector(static_cast<float>(_cx), static_cast<float>(_cy)); }

public:
	Sprite(Texture* texture, int x, int y, int cx, int cy);
	virtual ~Sprite();
};