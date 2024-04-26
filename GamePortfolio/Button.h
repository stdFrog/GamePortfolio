#pragma once
#include "UI.h"
#include "Sprite.h"

enum ButtonState {
	BS_DEFAULT,
	BS_PRESSED,
	BS_CLICKED,

	BUTTON_STATE_LAST_COUNT
};

/*
	버튼이나 리스트 박스 등의 컨트롤 즉, UI가 상용 엔진에서 어떻게 변화했는지 모르겠으나,
	강의를 듣다보면 그래픽과 윈도우의 차이를 잘 모르는 것 같다.
	
	최신의 상용 엔진에선 커스텀 컨트롤의 제작이 꽤 희귀한 것으로 보이며,
	아래와 같이 버튼 클래스를 따로 만든다 하여도 동작이 단순하고 전체 로직 역시 간단하여
	윈도우 컨트롤만큼의 동작도 하지 않는 것으로 보인다.

	실무에서도 이와 같이 간단히 작성할 것으로 예상된다.
	사실 이 정도라면 굳이 클래스를 따로 설계할 필요도 없다.

	커스텀 컨트롤은 전체 프로젝트에서 공통으로 사용할 목적을 갖고 제작한다.

	곧, 어디서나 쓰일 수 있는 일반화 또는, 최적화 된 클래스를 말하며,
	프로젝트와 함께 운영체제에 등록되어야 하는 최상의 클래스이다.
*/
class Button : public UI
{
	using Super = UI;

protected:
	Sprite* _CurrentSprite = NULL;
	Sprite* _Sprites[BUTTON_STATE_LAST_COUNT];
	ButtonState _State = BS_DEFAULT;

	float _Sum = 0.f;

public:
	Sprite* GetSprite(ButtonState State) { return _Sprites[State]; }
	void SetCurrentSprite(Sprite* NewSprite) { _CurrentSprite = NewSprite; }
	void SetSprite(Sprite* NewSprite, ButtonState State) { _Sprites[State] = NewSprite; }
	void SetButtonState(ButtonState State);


public:
	Button();
	virtual ~Button();

	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};

