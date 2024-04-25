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

	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	Vector CameraPosition = Scene->GetMainCamera().GetTransform().GetPosition();

	LONG Width, Height;
	WindowsUtility::GetWindowSize(GetForegroundWindow(), &Width, &Height);

	// 트랜스폼 정보를 사용하지 않았을 때(SpriteActor)
	// 프로젝트 시작부터 강의에서 800 x 600 크기로 맞춰놨기 때문에
	// 뷰 포트 해상도에 맞게 하드 코딩함
	TransparentBlt(hDC,
		static_cast<int>(_Position.x - Size.x - (CameraPosition.x - (Width - 264) / 2)),
		static_cast<int>(_Position.y - Size.y - (CameraPosition.y - Height / 2)),
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