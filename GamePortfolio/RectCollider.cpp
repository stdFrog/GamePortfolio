#include "pch.h"
#include "RectCollider.h"
#include "CircleCollider.h"
#include "Actor.h"

RectCollider::RectCollider() : Collider(ColliderType::Rect) {

}

RectCollider::~RectCollider() {

}

BOOL RectCollider::Initialize() {
	Super::Initialize();

	return TRUE;
}

void RectCollider::Update(float dtSeconds) {
	Super::Update(dtSeconds);


}

void RectCollider::Render(HDC hDC) {
	Super::Render(hDC);

	if (_bVisible == FALSE) { return; }
	BaseScene* Scene = GetOwner()->GetScene();
	Vector Camera = Scene->GetMainCamera().GetTransform().GetPosition();
	Vector Position = GetOwner()->GetPosition();

	LONG Width, Height;
	WindowsUtility::GetWindowSize(GetForegroundWindow(), &Width, &Height);
	Position.x -= (Camera.x - (Width - 264) / 2);
	Position.y -= (Camera.y - Height / 2);

	WindowsUtility::DrawRect(hDC, Position, _Size.x, _Size.y);
}

BOOL RectCollider::CheckCollision(Collider* Other) {
	if (Super::CheckCollision(Other) == FALSE) { return FALSE; }
	BOOL(*fp)(Collider*, Collider*) = Collider::Select(this, Other);
	BOOL(*pfn)(Collider*, Collider*) = Collider::PushOutCollider(this, Other);

	return (*fp)(this, Other) && (*pfn)(this, Other);
}