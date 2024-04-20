#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"

SpriteActor::SpriteActor() {

}

SpriteActor::~SpriteActor() {
	
}

BOOL SpriteActor::Initialize() {
	// Super::Initialize();

	return TRUE;
}

void SpriteActor::Update(float dtSeconds) {
	// Super::Update(dtSeconds);
}

void SpriteActor::Render(HDC hDC) {
	// Super::Render(hDC);

	if (_Sprite == NULL) {
		return;
	}

	Vector Size = _Sprite->GetSize();

	BitBlt(hDC,
		_Position.x - Size.x / 2,
		_Position.y - Size.y / 2,
		WindowsUtility::WindowsSize.x,
		WindowsUtility::WindowsSize.y,
		_Sprite->GetSpriteDC(),
		_Sprite->GetPosition().x,
		_Sprite->GetPosition().y,
		SRCCOPY);
}