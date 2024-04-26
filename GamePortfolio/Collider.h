#pragma once
#include "Component.h"

enum class ColliderType {
	Rect,
	Circle,
	Point,
	Line
};

/*
	충돌 처리를 위한 영역이자 물체를 구성하는 메시로 볼 수 있다.

	정점 버퍼를 만들고 삼각형을 이어 붙여 물체를 구성하는 것이 일반적이지만,
	이처럼 간단한 방법으로도 구현할 수 있다고 한다.

	평면에서의 충돌 가능한 영역은 평면 도형으로부터 구할 수 있으므로
	다음과 같이 사각형, 원형, 다각형, 점, 직선 등을 이용한다.

	WinApi에서 지원하는 작도 함수가 있으므로 이를 응용해도 좋다.
*/
class Collider : public Component
{
	std::unordered_set<Collider*> _ColliderSet;

protected:
	ColliderType _Type;
	BOOL _bVisible = TRUE;

public:
	std::unordered_set<Collider*>& GetColliderSet() { return _ColliderSet; }
	const std::unordered_set<Collider*>& GetColliderSet() const { return _ColliderSet; }

public:
	static BOOL (*Select(Collider* P1, Collider* P2))(Collider*, Collider*);
	static BOOL CollisionCircleToCircle(Collider*, Collider*);
	static BOOL CollisionRectToRect(Collider*, Collider*);
	
public:
	static BOOL CollisionPointToRect(Collider*, Collider*);
	static BOOL CollisionLineToRect(Collider*, Collider*);
	static BOOL CollisionCircleToRect(Collider*, Collider*);

public:
	static BOOL CollisionPointToCircle(Collider*, Collider*);
	static BOOL CollisionLineToCircle(Collider*, Collider*);

public:
	static BOOL CollisionPointToLine(Collider*, Collider*);

public:
	void SetVisible(BOOL bVisible) { _bVisible = bVisible; }
	ColliderType GetColliderType() { return _Type; }

public:
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
	virtual BOOL CheckCollision(Collider* Other);

public:
	Collider(ColliderType Type = ColliderType::Rect);
	virtual ~Collider();
};