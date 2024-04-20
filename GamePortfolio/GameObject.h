#pragma once
#include "Objectinterface.h"
/*
	엔진측 코드

	- GameObject는 유니티의 스타일을 따라한 위한 임시 클래스이다.

	기반 클래스로서 ObjectInterface의 모든 기능을 그대로 가져야 한다.
	그러나 현재 프로젝트에선 이미 일전에 만들어둔 객체가 있으므로
	단순 파생 클래스로 활용하기로 한다.

	씬을 구성하는 객체는 결국 ObjectInterface의 원형과 다르지 않다.

	유니티에선 등장인물에 텍스쳐를 입히기 위한 방법으로 컴포넌트를 사용한다.
	아무것도 없는 단순한 클래스를 만들고 기능을 이어붙인다는 의미이다.
*/

class Component;

class GameObject : ObjectInterface
{
protected:
	std::vector<Component*> _Components;

public:
	void AddComponent(Component*);

public:
	GameObject();
	virtual ~GameObject();

	virtual BOOL Initialize();			// Start
	virtual void Update(float);			// Update
	virtual void Render(HDC);			// Render
};

