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
	현대의 엔진을 보면 그래픽 컨트롤과 윈도우 컨트롤의 차이를 따질 필요가 없는 것으로 보인다.
	
	최신의 상용 엔진에선 프레임 관리를 위해 메세지 루프를 이 프로젝트와 동일하게 관리한다.
	
	즉, 커스텀 컨트롤의 메시지 루프를 활용할 기회가 없으므로 그래픽 컨트롤을 사용한다.
	아래와 같이 버튼 클래스를 만들고 단순한 동작과 함수만을 설계하면 나름 쓸만한 것으로 보인다.

	윈도우 컨트롤만큼의 자동화는 이루어지지 않지만 속도상 유리하므로 아래 방법을 채택한 것 같다.
*/

/*
	입력을 받는 클래스의 경우 활성 상태와 키보드 입력 상태를 확인하는 것이 우선이다.
	또한, 버튼 클래스의 경우 핫 상태의 처리가 굉장히 중요한데, 리소스가 준비되지 않았으므로
	넘어가기로 하자. 추후 개작할 시간이 있을 때 관련 기능을 추가하도록 한다.
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
	std::function<void(void)> _OnClick = NULL;

	template <typename T>
	void AddOnClickDelegate(T* Owner, void(T::* fn)()) {
		_OnClick = [Owner, fn]() {
			(Owner->*fn)();
		};
	}

public:
	Sprite* GetSprite(ButtonState State) { return _Sprites[State]; }
	void SetCurrentSprite(Sprite* NewSprite) { _CurrentSprite = NewSprite; }
	void SetSprite(Sprite* NewSprite, ButtonState State) { _Sprites[State] = NewSprite; }
	void SetButtonState(ButtonState State);
	void SetSize(Vector Size) { _Size = Size; }

public:
	Button(BaseScene* CurrentScene = NULL);
	virtual ~Button();

	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};

