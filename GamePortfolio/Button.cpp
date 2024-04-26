#include "pch.h"
#include "Button.h"

Button::Button() {

}

Button::~Button() {

}

BOOL Button::Initialize() {
	Super::Initialize();
	SetButtonState(BS_DEFAULT);

	return TRUE;
}

void Button::Update(float dtSeconds) {
	const auto& Engine = (GameEngine*)_Owner->GetInstance();
	auto& Input = Engine->GetInputManager();

	POINT Mouse = Input.GetMousePosition();
	if (IsMouseInRect()) {
		WindowsUtility::Trace(TEXT("Calling IsMouseIntRect"));
	}
	else 
	{
	
	}
}

void Button::Render(HDC hDC) {
	if (_CurrentSprite) {
		TransparentBlt(
			hDC,
			static_cast<int>(_Position.x - _Size.x / 2),
			static_cast<int>(_Position.y - _Size.y / 2),
			static_cast<int>(_Size.x),
			static_cast<int>(_Size.y),
			_CurrentSprite->GetSpriteDC(),
			static_cast<int>(_CurrentSprite->GetPosition().x),
			static_cast<int>(_CurrentSprite->GetPosition().y),
			static_cast<int>(_CurrentSprite->GetSize().x),
			static_cast<int>(_CurrentSprite->GetSize().y),
			_CurrentSprite->GetTransparent()
		);
	}
	else {
		WindowsUtility::DrawRect(hDC, _Position, _Size.x, _Size.y);
	}
}

void Button::SetButtonState(ButtonState State) {
	_State = State;

	if (_Sprites[State]) {
		SetCurrentSprite(_Sprites[State]);
	}
}