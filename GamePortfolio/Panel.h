#pragma once
#include "UI.h"

class Sprite;

/*
	UI 객체를 하나로 묶어 관리하는 클래스이다.
	언리얼 및 유니티에서도 같은 이름의 클래스가 존재한다.

	원조는 앱바 정도로 볼 수 있다.
	쉘의 앱바와 비슷한 용도의 클래스이며 단순히 UI의 파생 클래스들을 모아서 관리할 때 활용된다.
*/
class Panel : public UI
{
	using Super = UI;
	std::vector<UI*> _Childs;

public:
	void AddChild(UI* NewInterface);
	BOOL RemoveChild(UI* Target);

public:
	virtual BOOL Initilaize();
	virtual void Update(float);
	virtual void Render(HDC);

public:
	Panel(BaseScene* CurrentScene = NULL);
	virtual ~Panel();
};

