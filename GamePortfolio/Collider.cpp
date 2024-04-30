#include "pch.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "RectCollider.h"

Collider::Collider(ColliderType Type) : _Type(Type) {

}

Collider::~Collider() {

}

BOOL Collider::Initialize() {
	return TRUE;
}

void Collider::Update(float dtSeconds) {

}

void Collider::Render(HDC hDC) {

}

BOOL Collider::CheckCollision(Collider* Other) {

	return FALSE;
}

BOOL (*Collider::Select(Collider* P1, Collider* P2))(Collider*, Collider*){
	int TypeOne = static_cast<int>(P1->GetColliderType());
	int TypeTwo = static_cast<int>(P2->GetColliderType());

	int XOR = TypeOne ^ TypeTwo;
	int Sum = TypeOne + TypeTwo;

	if (XOR) {
		switch (XOR) {
		case 1:
			if (TypeOne > XOR || TypeTwo > XOR) { return Collider::CollisionPointToLine; }
			return Collider::CollisionCircleToRect;
			
		case 2:
			if (TypeOne > XOR || TypeTwo > XOR) { return Collider::CollisionLineToCircle; }
			return Collider::CollisionPointToRect;
			
		case 3:
			if (TypeOne > XOR || TypeTwo > XOR) { return Collider::CollisionPointToCircle; }
			return Collider::CollisionLineToRect;
			
		default:
			break;
		}
	}
	else {
		switch (Sum) {
		case 0:
			return Collider::CollisionRectToRect;

		case 2:
			return Collider::CollisionCircleToCircle;

		case 4:
			/*
				Point : 접촉한 도형의 방정식과 해당 점의 좌표가 주어지면 자취의 방정식을 구할 수 있다.
				곧, 얼마만큼 떨어져 있는가를 알 수 있다.
			*/
			break;

		case 6:
			/*
				Line: 점과 직선 사이의 거리 구하는건 그리 어렵지 않다.
				대신 게임에서 설계할 때는 점이 직접 주어지는 경우는 없으므로,
				레이어를 계산할 함수를 따로 준비하는 것이 좋을 것 같다.
			*/
			break;

		default:
			break;
		}
	}

	return NULL;
}

BOOL Collider::CollisionCircleToCircle(Collider* P1, Collider* P2) {
	CircleCollider* CastOne = dynamic_cast<CircleCollider*>(P1);
	CircleCollider* CastTwo = dynamic_cast<CircleCollider*>(P2);

	if (CastOne == NULL || CastTwo == NULL) { return FALSE; }

	Vector PositionOne = CastOne->GetOwner()->GetPosition();
	Vector PositionTwo = CastTwo->GetOwner()->GetPosition();

	float RadiusOne = CastOne->GetRadius();
	float RadiusTwo = CastTwo->GetRadius();

	Vector Sub = PositionOne - PositionTwo;
	float Distance = Sub.length();

	return Distance <= (RadiusOne + RadiusTwo);
}

BOOL Collider::CollisionRectToRect(Collider* P1, Collider* P2) {
	RectCollider* CastOne = dynamic_cast<RectCollider*>(P1);
	RectCollider* CastTwo = dynamic_cast<RectCollider*>(P2);

	if (CastOne == NULL || CastTwo == NULL) { return FALSE; }

	Vector PositionOne = CastOne->GetOwner()->GetPosition();
	Vector PositionTwo = CastTwo->GetOwner()->GetPosition();

	Vector RectOne = CastOne->GetSize();
	Vector RectTwo = CastTwo->GetSize();

	Vector L1, R1;
	L1 = Vector(
		GameMath::MIN(PositionOne.x, PositionOne.x - RectOne.x / 2),
		GameMath::MIN(PositionOne.y, PositionOne.y - RectOne.y / 2)
	);

	R1 = Vector(
		GameMath::MAX(PositionOne.x, PositionOne.x + RectOne.x / 2),
		GameMath::MAX(PositionOne.y, PositionOne.y + RectOne.y / 2)
	);
	
	Vector L2, R2;
	L2 = Vector(
		GameMath::MIN(PositionTwo.x, PositionTwo.x - RectTwo.x / 2),
		GameMath::MIN(PositionTwo.y, PositionTwo.y - RectTwo.y / 2)
	);

	R2 = Vector(
		GameMath::MAX(PositionTwo.x, PositionTwo.x + RectTwo.x / 2),
		GameMath::MAX(PositionTwo.y, PositionTwo.y + RectTwo.y / 2)
	);

	if (R1.x < L2.x) {
		return FALSE;
	}

	if (R1.y < L2.y) {
		return FALSE;
	}

	if (R2.x < L1.x) {
		return FALSE;
	}

	if (R2.y < L1.y) {
		return FALSE;
	}

	return TRUE;
}

BOOL Collider::CollisionPointToRect(Collider* P1, Collider* P2) {
	return FALSE;
}

BOOL Collider::CollisionLineToRect(Collider* P1, Collider* P2) {
	return FALSE;
}
BOOL Collider::CollisionCircleToRect(Collider* P1, Collider* P2) {
	BOOL bCircle = (P1->GetColliderType() == ColliderType::Circle);

	CircleCollider* Circle = static_cast<CircleCollider*>(((bCircle) ? (P1) : (P2)));
	RectCollider* Rectangle = static_cast<RectCollider*>(((bCircle) ? (P2) : (P1)));
	
	Vector RectPosition = Rectangle->GetOwner()->GetPosition();
	Vector CirclePosition = Circle->GetOwner()->GetPosition();

	Vector RectSize = Rectangle->GetSize();
	float Radius = Circle->GetRadius();

	RECT NormalRect = {
		RectPosition.x - RectSize.x / 2,
		RectPosition.y - RectSize.y / 2,
		RectPosition.x + RectSize.x / 2,
		RectPosition.y + RectSize.y / 2
	};
	
	if ((NormalRect.left <= CirclePosition.x && NormalRect.right >= CirclePosition.x) ||
		(NormalRect.top <= CirclePosition.y && NormalRect.bottom >= CirclePosition.y)) {

		RECT ExpandRectangle = {
			NormalRect.left - Radius,
			NormalRect.top - Radius,
			NormalRect.right + Radius,
			NormalRect.bottom + Radius
		};

		if (ExpandRectangle.left < CirclePosition.x && CirclePosition.x < ExpandRectangle.right) {
			if (ExpandRectangle.top < CirclePosition.y && CirclePosition.y < ExpandRectangle.bottom) {
				return TRUE;
			}
		}
	}
	else {
		if (IsPointInCircle(CirclePosition, Vector(NormalRect.left, NormalRect.top), Radius)) {
			return TRUE;
		}
		if (IsPointInCircle(CirclePosition, Vector(NormalRect.left, NormalRect.bottom), Radius)) {
			return TRUE;
		}
		if (IsPointInCircle(CirclePosition, Vector(NormalRect.right, NormalRect.top), Radius)) {
			return TRUE;
		}
		if (IsPointInCircle(CirclePosition, Vector(NormalRect.right, NormalRect.bottom), Radius)) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL Collider::CollisionPointToCircle(Collider* P1, Collider* P2) {
	return FALSE;
}

BOOL Collider::CollisionLineToCircle(Collider* P1, Collider* P2){
	return FALSE;
}

BOOL Collider::CollisionPointToLine(Collider* P1, Collider* P2) {
	return FALSE;
}


BOOL Collider::IsPointInCircle(Vector Circle, Vector RectSide, float Radius) {
	float dx, dy, dist, R2;

	dx = Circle.x - RectSide.x;
	dy = Circle.y - RectSide.y;

	dist = Vector(dx, dy).length();

	if (dist < Radius) {
		return TRUE;
	}

	return FALSE;
}