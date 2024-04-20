#include "pch.h"
#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

BOOL Player::Initialize() {
	// Super::Initialize();

	return TRUE;
}

void Player::Update(float dtSeconds) {
	// Super::Update(dtSeconds);

	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	const auto& Engine = (GameEngine*)Scene->GetInstance();
	auto& Input = Engine->GetInputManager();

	if (Input.IsPressed(InputButton::W)) {
		WindowsUtility::Trace(L"Hello World");
	}
}

void Player::Render(HDC hDC) {
	// Super::Render(hDC);
}