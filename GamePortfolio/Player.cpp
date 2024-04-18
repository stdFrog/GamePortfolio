#include "pch.h"
#include "Bullet.h"

Player::Player(ObjectType Type) : ObjectInterface(ObjectType::Player){

}

Player::~Player() {

}

BOOL Player::Initialize() {
	_Status.HP = 100;
	_Status.MP = 100;
	_Status.MaxHP = 100;
	_Status.MaxMP = 100;
	_Status.Speed = 500.f;

	return TRUE;
}

void Player::Update(float dtSeconds) {
	const auto& Engine = ((BaseScene*)_Scene)->GetInstance();
	auto& Input = ((GameEngine*)Engine)->GetInputManager();

	FortressScene* CurrentScene = dynamic_cast<FortressScene*>(_Scene);
	if (CurrentScene == NULL) { return; }

	auto& UI = CurrentScene->GetUserInterface();

	if (_PlayerTurn == FALSE) { return; }

	UpdateFireAngle();

	float XAxis = 0.f;
	float AngleAxis = 0.f;

	BOOL Left = Input.IsPressed(InputButton::A);
	BOOL Right = Input.IsPressed(InputButton::D);
	BOOL AngleUp = Input.IsPressed(InputButton::W);
	BOOL AngleDown = Input.IsPressed(InputButton::S);
	BOOL E = Input.IsPressed(InputButton::E);
	BOOL Q = Input.IsPressed(InputButton::Q);
	BOOL SpaceDown = Input.IsPressed(InputButton::SpaceBar);
	BOOL SpaceUp = Input.IsRelease(InputButton::SpaceBar);

	if (Left ^ Right) {	XAxis = ((Left) ? (_Direction = Direction::Left, (-1.f)) : (_Direction = Direction::Right, (1.f))); }
	if (AngleUp) {
		_FireAngle = GameMath::CLAMP(0.f, 75.f, _FireAngle + 50 * dtSeconds);

	}
	else if(AngleDown){
		_FireAngle = GameMath::CLAMP(0.f, 75.f, _FireAngle - 50 * dtSeconds);
	}

	if (SpaceDown) { 
		float percent = UI.GetPowerPercent();

		percent = min(100, percent + 100 * dtSeconds);
		UI.SetPowerPercent(percent);
	}

	if (SpaceUp) {
		_PlayerTurn = FALSE;

		float percent = UI.GetPowerPercent();
		float angle = UI.GetBarrelAngle();
		float speed = 10.f * percent;

		// TODO : +물리적 연산
		Bullet* bullet = ((BaseScene*)_Scene)->CreateObject<Bullet>();
		bullet->SetPosition(_Position);
		bullet->SetSpeed(Vector(speed * cos(angle * GameMath::PI / 180.f), -1 * speed * sin(angle * GameMath::PI / 180.f)));
		((BaseScene*)_Scene)->AppendObject(bullet);
	}

	Vector Axis = Vector(XAxis, 0.f).GetNormalize();
	Vector DeltaPosition = Axis * _Status.Speed * dtSeconds;

	_Position += DeltaPosition;
}

void Player::Render(HDC hDC) {
	const auto& Engine = ((BaseScene*)_Scene)->GetInstance();
	LineMesh player = ((GameEngine*)Engine)->GetLineMesh(GetMeshName());

	if (_Direction == Direction::Left) {
		player.Render(hDC, _Position, 0.5f, 0.5f);
	}
	else {
		player.Render(hDC, _Position, -0.5f, 0.5f);
	}

	if (_PlayerTurn) {
		RECT prt = {0,0,0,0};

		prt.left = (LONG)(_Position.x - 10);
		prt.right = (LONG)(_Position.x + 10);
		prt.top = (LONG)(_Position.y - 80);
		prt.bottom = (LONG)(_Position.y - 60);

		HBRUSH hBrush = CreateSolidBrush(RGB(250, 236, 197));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		Ellipse(hDC, prt.left, prt.top, prt.right, prt.bottom);

		DeleteObject(SelectObject(hDC, hOldBrush));
	}
}

std::wstring Player::GetMeshName() {
	if (_PlayerType == PlayerType::MissileTank) {
		return L"MissileTank";
	}

	return L"CanonTank";
}

void Player::UpdateFireAngle() {
	FortressScene* CurrentScene = dynamic_cast<FortressScene*>(_Scene);

	if (CurrentScene) {
		auto& UI = ((FortressScene*)_Scene)->GetUserInterface();

		if (_Direction == Direction::Left) {
			UI.SetPlayerAngle(180);
			UI.SetBarrelAngle(180 - _FireAngle);
		}
		else {
			UI.SetPlayerAngle(0);
			UI.SetBarrelAngle(_FireAngle);
		}
	}
}