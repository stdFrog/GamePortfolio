#include "pch.h"
#include "SpriteRenderer.h"
#include "Sprite.h"

BOOL SpriteRenderer::Initialize() {
	return TRUE;
}

void SpriteRenderer::Update(float dtSeconds) {

}

void SpriteRenderer::Render(HDC hDC) {
	if (_Sprite == NULL) { return; }

	// Vector Size = _Sprite->GetSize();

	/*
	BitBlt(hDC,
		_Position.x - Size.x / 2,
		_Position.y - Size.y / 2,
		WindowsUtility::WindowsSize.x,
		WindowsUtility::WindowsSize.y,
		_Sprite->GetSpriteDC(),
		_Sprite->GetPosition().x,
		_Sprite->GetPosition().y,
		SRCCOPY);
	*/
}