#include "pch.h"

Missile::Missile(ObjectType Type) : ObjectInterface(ObjectType::Projectile) {

}

Missile::~Missile() {

}

BOOL Missile::Initialize() {
	_Status.HP = 1;
	_Status.MaxHP = 1;
	_Status.Speed = 500.f;
	
	return TRUE;
}

void Missile::Update(float dtSeconds) {
	const auto& Scene = (BaseScene*)_Scene;

	_Position.y -= dtSeconds * _Status.Speed;

	const std::vector<ObjectInterface*> Objects = Scene->GetObjects();
	for (ObjectInterface* Target : Objects) {
		if (Target == this) { continue; }
		if (Target->GetObjectType() != ObjectType::Monster) { continue; }

		Vector P1 = GetPosition();
		Vector P2 = Target->GetPosition();

		const float dx = P1.x - P2.x;
		const float dy = P1.y - P2.y;

		float dist = GameMath::Sqrt(dx * dx + dy * dy);
		if (dist < 25) {
			// 순서 주의
			Scene->RemoveObject(Target);
			Scene->RemoveObject(this);
			return;
		}
	}

	if (_Position.y < -100) {
		Scene->RemoveObject(this);
		return;
	}
}

void Missile::Render(HDC hDC) {
	WindowsUtility::DrawCircle(hDC, _Position, 25);
}