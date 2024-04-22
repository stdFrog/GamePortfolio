#include "pch.h"
#include "Player.h"
#include "Flipbook.h"

Player::Player() : FlipbookActor(ObjectType::Player) {
	
}

Player::~Player() {

}

BOOL Player::Initialize() {
	Super::Initialize();

	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	const auto& Engine = (GameEngine*)(Scene->GetInstance());

	_FlipbookUp = Engine->GetFlipbook(L"FB_MoveUp");
	_FlipbookDown = Engine->GetFlipbook(L"FB_MoveDown");
	_FlipbookLeft = Engine->GetFlipbook(L"FB_MoveLeft");
	_FlipbookRight = Engine->GetFlipbook(L"FB_MoveRight");

	SetFlipbook(_FlipbookRight);

	return TRUE;
}

void Player::Update(float dtSeconds) {
	Super::Update(dtSeconds);

	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	const auto& Engine = (GameEngine*)(Scene->GetInstance());
	auto& Input = Engine->GetInputManager();

	float Speed = 200.f;

	if (Input.IsPressed(InputButton::W)) {
		_Position.y -= Speed * dtSeconds;
		SetFlipbook(_FlipbookUp);
	}
	else if (Input.IsPressed(InputButton::S)) {
		_Position.y += Speed * dtSeconds;
		SetFlipbook(_FlipbookDown);
	}
	else if (Input.IsPressed(InputButton::A)) {
		_Position.x -= Speed * dtSeconds;
		SetFlipbook(_FlipbookLeft);
	}
	else if (Input.IsPressed(InputButton::D)) {
		_Position.x += Speed * dtSeconds;
		SetFlipbook(_FlipbookRight);
	}
}

void Player::Render(HDC hDC) {
	Super::Render(hDC);

}