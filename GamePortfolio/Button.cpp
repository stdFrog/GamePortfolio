#include "pch.h"
#include "Button.h"

Button::Button(BaseScene* CurrentScene) : UI(CurrentScene){

}

Button::~Button() {

}

BOOL Button::Initialize() {
	Super::Initialize();
	SetButtonState(BS_DEFAULT);
	return TRUE;
}

void Button::Update(float dtSeconds) {
	// 입력을 받을 때는 항상 Foreground 또는 Active(키보드 입력 가능)상태인지
	// 확인하는 것이 우선이다. 실습에선 이런 내용을 다루지 않지만 항상 기억해둬야 한다.
	
	// 버튼을 눌렀을 때 컨텐츠 측에서 필요한 동작이 있다면 마땅히 처리해야 한다.
	// 곧, 엔진 개발자 입장에선 이러한 처리가 가능하도록 콜백 함수를 지원해야 한다는 뜻이다.

	const auto& Engine = (GameEngine*)_Owner->GetInstance();
	auto& Input = Engine->GetInputManager();

	if (_State == BS_CLICKED) {
		_Sum += dtSeconds;
		if (_Sum >= 0.2f) {
			_Sum = 0.f;
			SetButtonState(BS_DEFAULT);
		}
	}

	POINT Mouse = Input.GetMousePosition();
	if (IsMouseInRect()) {
		WindowsUtility::Trace(TEXT("Calling IsMouseIntRect"));
		if (Input.IsPressed(InputButton::LeftMouse)) {
			SetButtonState(BS_PRESSED);
			// 컨텐츠 측에서 해당 버튼의 동작을 정의할 수 있도록 콜백 함수를 전달한다.
		}
		else {
			if (_State == BS_PRESSED) {
				SetButtonState(BS_CLICKED);
				// 컨텐츠 측에서 해당 버튼의 동작을 정의할 수 있도록 콜백 함수를 전달한다.
				if (_OnClick) {
					_OnClick();
				}
			}
		}
	}
	else 
	{
		SetButtonState(BS_DEFAULT);
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