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
	
	if (Scene){
		// Wind, Gravity
		auto& UI = Scene->GetUserInterface();

		_Position += _Speed * dtSeconds;
		if (_Position.y > UI.GWinSizeY * 1.5 || _Position.y < (-UI.GWinSizeY) * 1.5) {
			Scene->ChangePlayerTurn();
			
			((BaseScene*)_Scene)->RemoveObject(this);
			return;
		}
	}
}

void Bullet::Render(HDC hDC) {
	WindowsUtility::DrawCircle(hDC, _Position, _Radius);
}