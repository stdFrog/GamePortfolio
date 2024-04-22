#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"

SpriteActor::SpriteActor(ObjectType Type) : Actor(Type){

}

SpriteActor::~SpriteActor() {
	
}

BOOL SpriteActor::Initialize() {
	Super::Initialize();

	return TRUE;
}

void SpriteActor::Update(float dtSeconds) {
	Super::Update(dtSeconds);
}

void SpriteActor::Render(HDC hDC) {
	Super::Render(hDC);

	if (_Sprite == NULL) {
		return;
	}

	Vector Size = _Sprite->GetSize();

	/*BitBlt(hDC,
		_Position.x - Size.x / 2,
		_Position.y - Size.y / 2,
		WindowsUtility::WindowsSize.x,
		WindowsUtility::WindowsSize.y,
		_Sprite->GetSpriteDC(),
		_Sprite->GetPosition().x,
		_Sprite->GetPosition().y,
		SRCCOPY);*/
	TransparentBlt(hDC,
		static_cast<int>(_Position.x - Size.x / 2),
		static_cast<int>(_Position.y - Size.y / 2),
		static_cast<int>(Size.x),
		static_cast<int>(Size.y),
		_Sprite->GetSpriteDC(),
		static_cast<int>(_Sprite->GetPosition().x),
		static_cast<int>(_Sprite->GetPosition().y),
		static_cast<int>(_Sprite->GetSize().x),
		static_cast<int>(_Sprite->GetSize().y),
		_Sprite->GetTransparent()
	);
}