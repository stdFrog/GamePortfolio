#include "pch.h"
#include "CircleCollider.h"
#include "RectCollider.h"

CircleCollider::CircleCollider() : Collider(ColliderType::Circle) {

}

CircleCollider::~CircleCollider() {

}

BOOL CircleCollider::Initialize() {
	Super::Initialize();
	
	return TRUE;
}

void CircleCollider::Update(float dtSeconds) {
	Super::Update(dtSeconds);

}

void CircleCollider::Render(HDC hDC) {
	Super::Render(hDC);

	if (_bVisible == FALSE) { return; }
	BaseScene* Scene = GetOwner()->GetScene();
	Vector Camera = Scene->GetMainCamera().GetTransform().GetPosition();
	Vector Position = GetOwner()->GetPosition();

	LONG Width, Height;
	WindowsUtility::GetWindowSize(GetForegroundWindow(), &Width, &Height);
	Position.x -= (Camera.x - (Width - 264) / 2);
	Position.y -= (Camera.y - Height / 2);

	WindowsUtility::DrawCircle(hDC, Position, _Radius);
}

BOOL CircleCollider::CheckCollision(Collider* Other) {
	if (Super::CheckCollision(Other) == FALSE) { return FALSE; }
	BOOL(*fp)(Collider*, Collider*) = Collider::Select(this, Other);
	BOOL(*pfn)(Collider*, Collider*) = Collider::PushOutCollider(this, Other);
	return (*fp)(this, Other) && (*pfn)(this, Other);
}