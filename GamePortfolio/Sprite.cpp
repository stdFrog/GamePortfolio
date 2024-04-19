#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite(Texture* texture, int x, int y, int cx, int cy) :
	_Texture(texture), _x(x), _y(y), _cx(cx), _cy(cy), _hDC(NULL)
{

}

Sprite::~Sprite() {

}

HDC Sprite::GetSpriteDC() { return _Texture->GetTextureDC(); }
int Sprite::GetTransparent(){ return _Texture->GetTransParent(); }