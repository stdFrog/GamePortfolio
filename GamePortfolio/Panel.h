#pragma once
class UI;
/*
	UI 객체를 하나로 묶어 관리하는 클래스이다.
	언리얼 및 유니티에서도 같은 이름의 클래스가 존재한다.

	원조는 앱바 정도로 볼 수 있다.
	쉘의 앱바와 비슷한 용도의 클래스이며 단순히 UI의 파생 클래스들을 모아서 관리할 때 활용된다.
	===========================================================================================
	UI 실습 이후 구조를 개선했다.
	기존엔 Panel이라는 관리 객체가 UI 클래스를 상속받는 구조로 작성되었다.
	
	그러나, 이는 논리적으로 맞지 않다고 판단하여 포함 관계로 변경했다.

	구조를 보면, Panel이 UI를 소유한 채로 각 UI의 관리 함수를 호출한다.
	또, 등장 요소를 관리하는 최상위 클래스인 씬에서도 Panel만을 생성해 관리하고 있다.
	
	따라서, 엔진측에서 관리해야 될 리소스는 Panel만을 대상으로 한다.
*/
class Panel
{
protected:
	BaseScene* _Owner;
	std::vector<UI*> _Childs;

public:
	BaseScene* GetOwner() { return _Owner; }

public:
	void AddChild(UI* NewInterface);
	BOOL RemoveChild(UI* Target);

public:
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);

public:
	Panel(BaseScene* CurrentScene);
	virtual ~Panel();
};

