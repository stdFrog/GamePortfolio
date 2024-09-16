#pragma once
// #include "Objectinterface.h"

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

/*
	게임 내 등장할 요소들을 GameObject로 구분하고 기반 클래스를 FlipbookActor로 변환하였다.
	중복 변수와 인터페이스가 사라졌다.
*/
class GameObject : public FlipbookActor // ObjectInterface
{
	using Super = FlipbookActor;

protected:
	// std::vector<Component*> _Components;

public:
	// void AppendComponent(Component*);

	BOOL MoveTo(Vector Position);
	BOOL HasReachedDest();

protected:
	DIRECTION _Direction = DIRECTION_DOWN;
	void SetDirection(DIRECTION Direction);

protected:
	Vector _CellPosition;
	Vector _Destination;
	OBJECTSTATE _State = OBJECTSTATE::IDLE;

public:
	void SetCellPosition(Vector Position, BOOL Teleport = FALSE);
	Vector GetCellPosition() { return _CellPosition; }

protected:
	void SetState(OBJECTSTATE State);
	OBJECTSTATE GetState() { return _State; }

protected:
	virtual void UpdateIdle(float) {}
	virtual void UpdateMove(float) {}
	virtual void UpdateSkill(float) {}
	
	virtual void UpdateAnimation() {}

public:
	GameObject(ObjectType Type = ObjectType::None);
	virtual ~GameObject();

	virtual BOOL Initialize();			// Start
	virtual void Update(float);			// Update
	virtual void Render(HDC);			// Render
};

