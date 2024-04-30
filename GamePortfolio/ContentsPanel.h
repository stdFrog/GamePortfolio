#pragma once
#include "Panel.h"

/*
	엔진측의 Panel 클래스로부터 파생되어 콘텐츠측에서 사용할 임시 클래스이다.

	버튼과 마찬가지로 실습을 위해 임시로 생성한 클래스이며,
	콘텐츠측에서 패널의 동작을 정의할 수 있도록 콜백 함수를 지원한다.
*/
class ContentsPanel : public Panel
{
	using Super = Panel;

	int _Count = 0;

public:
	void OnClickStartButton();
	void OnClickEditButton();
	void OnClickExitButton();

public:
	virtual BOOL Initilaize();
	virtual void Update(float);
	virtual void Render(HDC);

public:
	ContentsPanel(BaseScene* CurrentScene = NULL);
	virtual ~ContentsPanel();
};

