#include "pch.h"
#include "Bullet.h"

Bullet::Bullet() : ObjectInterface(ObjectType::Projectile) {

}

Bullet::~Bullet() {

}

BOOL Bullet::Initialize() {
	_Radius = 20.f;

	return TRUE;
}

void Bullet::Update(float dtSeconds) {
	FortressScene* Scene = dynamic_cast<FortressScene*>(_Scene);
	if (Scene == NULL) { return; }
	
	auto& UI = Scene->GetUserInterface();

	// Gravity(=Accel)
	Vector G(0, 800.f * dtSeconds);
	_Speed += G;

	// Wind
	Vector Wind(UI.GetWindPercent() * 10.f * dtSeconds, 0.f);
	_Speed += Wind;

	_Position += _Speed * dtSeconds;
	for (ObjectInterface* Object : _Scene->GetObjects()) {
		if (Object->GetObjectType() != ObjectType::Player) {
			continue;
		}
		if (Object == _Owner) {
			continue;
		}

		Vector Dest = _Position - Object->GetPosition();
		if (Dest.length() < _Radius + Object->GetRadius()) {
			// 피격 이미지, 피격 데미지 등등 애니메이션이나 필요한 처리 추가
			Scene->ChangePlayerTurn();

			((BaseScene*)_Scene)->RemoveObject(this);
			return;
		}
	}

	if (_Position.y > UI.GWinSizeY * 1.5 || _Position.y < (-UI.GWinSizeY) * 1.5) {
		Scene->ChangePlayerTurn();
			
		((BaseScene*)_Scene)->RemoveObject(this);
		return;
	}
}

void Bullet::Render(HDC hDC) {
	WindowsUtility::DrawCircle(hDC, _Position, _Radius);
}