#pragma once
#include "Button.h"
/*
	엔진측에서 UI 및 베이스 버튼 클래스 설계
	컨텐츠 측에서 사용하는 방법을 예시로 만들어보면 다음과 같다.

	사실 이와 같은 설계는 UI의 개수가 많지 않기 때문에 가능한 방법이다.

	UI가 수천개 수만개까지 늘어난다고 생각해보자.

*/
class ContentsButton : public Button
{
	using Super = Button;

public:
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);

public:
	ContentsButton();
	virtual ~ContentsButton();
};

