#include "pch.h"
#include "CameraComponent.h"

CameraComponent::CameraComponent() {

}

CameraComponent::~CameraComponent() {

}

BOOL CameraComponent::Initialize() {
	return TRUE;
}

void CameraComponent::Update(float) {
	if (_Owner == NULL) {
		return;
	}

	Vector Position = _Owner->GetPosition();

	BaseScene* Scene = _Owner->GetScene();
	Scene->GetMainCamera().GetTransform().SetPosition(
		Vector(
			GameMath::CLAMP(400.f, 3024.f - (400.f + 264.f), Position.x),
			GameMath::CLAMP(300.f, 2064.f - 300.f, Position.y)
		)
	);

		
}

void CameraComponent::Render(HDC) {

}