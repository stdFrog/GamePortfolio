#include "pch.h"

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
	const auto& Scene = (BaseScene*)_Scene;
	const auto& Engine = ((BaseScene*)_Scene)->GetInstance();
	auto& Input = ((GameEngine*)Engine)->GetInputManager();

	float XAxis = 0.f;
	float YAxis = 0.f;

	BOOL Left = Input.IsPressed(InputButton::A);
	BOOL Right = Input.IsPressed(InputButton::D);
	BOOL Up = Input.IsPressed(InputButton::W);
	BOOL Down = Input.IsPressed(InputButton::S);
	BOOL Space = Input.IsPressed(InputButton::SpaceBar);

	if (Left ^ Right) { XAxis = Left ? -1.f : 1.f; }
	if (Up ^ Down) { YAxis = Up ? -1.f : 1.f; }
	if (Space) { 
		// Missile* missile = new Missile();
		Missile* M = Scene->CreateObject<Missile>();
		M->SetPosition(_Position);
		Scene->AppendObject(M);
	}

	Vector Axis = Vector(XAxis, YAxis).GetNormalize();
	Vector DeltaPosition = Axis * _Status.Speed * dtSeconds;

	_Position += DeltaPosition;
}

void Player::Render(HDC hDC) {
	const auto& Engine = ((BaseScene*)_Scene)->GetInstance();
	auto& player = ((GameEngine*)Engine)->GetLineMesh(L"Player");

	player.Render(hDC, _Position);
}