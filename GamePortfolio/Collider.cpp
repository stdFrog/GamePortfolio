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

	UINT Layer = Other->GetCollisionLayerType();
	if (_CollisionFlag & 1 << Layer) {
		return TRUE;
	}

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
			break;

		case 6:
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

BOOL Collider::CollisionPointToRect(Collider* P1, Collider* P2) {
	BOOL bPoint = P1->GetColliderType() == ColliderType::Point;
	Vector Point = ((bPoint) ? (P1->GetOwner()->GetPosition()) : (P2->GetOwner()->GetPosition()));
	Vector Rectangle = ((bPoint) ? (P2->GetOwner()->GetPosition()) : (P1->GetOwner()->GetPosition()));
	Vector RectSize = ((bPoint) ? ((RectCollider*)P2)->GetSize() : ((RectCollider*)P1)->GetSize());

	RECT NormalRect = {
			Rectangle.x - RectSize.x,
			Rectangle.y - RectSize.y,
			Rectangle.x + RectSize.x,
			Rectangle.y + RectSize.y
	};

	if (NormalRect.left < Point.x && NormalRect.right > Point.x) {
		if (NormalRect.top < Point.y && NormalRect.bottom > Point.y) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL Collider::CollisionLineToRect(Collider* P1, Collider* P2) {
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
	float dx, dy, dist;

	dx = Circle.x - RectSide.x;
	dy = Circle.y - RectSide.y;

	dist = Vector(dx, dy).length();

	if (dist < Radius) {
		return TRUE;
	}

	return FALSE;
}

BOOL(*Collider::PushOutCollider(Collider* P1, Collider* P2))(Collider*, Collider*) {
	int Type1 = static_cast<int>(P1->GetColliderType());
	int Type2 = static_cast<int>(P2->GetColliderType());

	int XOR = Type1 ^ Type2;
	int Sum = Type1 + Type2;

	if (XOR) {
		switch (XOR) {
		case 1:
			if (Type1 > XOR || Type2 > XOR) { return Collider::CollisionPointToLine; }
			return Collider::CollisionCircleToRect;

		case 2:
			if (Type1 > XOR || Type2 > XOR) { return Collider::CollisionLineToCircle; }
			return Collider::CollisionPointToRect;

		case 3:
			if (Type1 > XOR || Type2 > XOR) { return Collider::CollisionPointToCircle; }
			return Collider::CollisionLineToRect;

		default:
			break;
		}
	}
	else {
		switch (Sum) {
		case 0:
			return Collider::PushOutRectToRect;

		case 2:
			return Collider::PushOutCircleToCircle;

		case 4:
			break;

		case 6:
			break;

		default:
			break;
		}
	}

	return NULL;
}

/*
	정해진 방법은 없으며, 당장 떠오르는 방법은 다음과 같다.
	
	두 원의 반지름의 합에서 두 원의 중심 사이의 거리를 뺀다. 이는 곧 겹쳐진 영역의 폭이 된다.
	동적 사물의 원의 중심. 곧, 대상의 좌표를 이 길이만큼 이동시킨다.

	원형이기 때문에 반지름의 길이가 항상 같으므로 방향 역시 단순 연산으로 구할 수 있다.
*/
BOOL Collider::PushOutCircleToCircle(Collider* P1, Collider* P2) {
	BOOL bTrue = FALSE;
	CircleCollider* Circle1 = static_cast<CircleCollider*>(P1);
	CircleCollider* Circle2 = static_cast<CircleCollider*>(P2);

	if (ObjectType::Player == Circle1->GetOwner()->GetObjectType()) {
		// 플레이어 간의 충돌은 가능한가?
		// 현재 주체를 대상으로 가정하여 조건식을 만들었으므로 상관없을 것으로 보인다.
		bTrue = TRUE;
	}

	Vector Position1, Position2;
	float Radius1, Radius2;

	Position1 = Circle1->GetOwner()->GetPosition();
	Position2 = Circle2->GetOwner()->GetPosition();

	Radius1 = Circle1->GetRadius();
	Radius2 = Circle2->GetRadius();

	float Sub = Radius2 - Radius1;
	float Sum = Radius2 + Radius1;
	float Length = (Position2 - Position1).length();

	Vector Result;
	LONG XAxis, YAxis;

	if (GameMath::ABS(Sub) < Length && Length < Sum) {
		// 접할 때
		XAxis = YAxis = 0;
		float Offset = Sum - Length;

		XAxis = (((Position1.x - Position2.x) < 0) ? -1 : 1);
		YAxis = (((Position1.y - Position2.y) < 0) ? -1 : 1);

		if (bTrue) {
			Result = Vector(Position1.x + XAxis * Offset, Position1.y + YAxis * Offset);
			P1->GetOwner()->SetPosition(Result);
		}
		else {
			Result = Vector(Position2.x + XAxis * Offset, Position2.y + YAxis * Offset);
			P2->GetOwner()->SetPosition(Result);
		}
	}

	return TRUE;
}

/*
	정해진 방법은 없다.

	수학적으로 계산하여 밀어내기만 하면 된다.
	아직은 타일을 적용하지 않은 상태이므로 부드러운 이동을 위해 각 축에 대해 동일하게 처리했다.

	추후 타일 단위로 이동하는 방식을 택하게 되면 충돌 코드 역시 바뀌어야 한다.
*/
BOOL Collider::PushOutRectToRect(Collider* P1, Collider* P2) {
	BOOL bTrue = FALSE;
	RectCollider* Rect1 = static_cast<RectCollider*>(P1);
	RectCollider* Rect2 = static_cast<RectCollider*>(P2);

	if (ObjectType::Player == Rect1->GetOwner()->GetObjectType()) {
		bTrue = TRUE;
	}

	Vector Position1, Position2;
	Vector RectSize1, RectSize2;
	RECT Rectangle1, Rectangle2, Intersect;

	Position1 = Rect1->GetOwner()->GetPosition();
	Position2 = Rect2->GetOwner()->GetPosition();

	RectSize1 = Rect1->GetSize() / 2;
	RectSize2 = Rect2->GetSize() / 2;

	Rectangle1 = {
		static_cast<LONG>(Position1.x - RectSize1.x),
		static_cast<LONG>(Position1.y - RectSize1.y),
		static_cast<LONG>(Position1.x + RectSize1.x),
		static_cast<LONG>(Position1.y + RectSize1.y)
	};

	Rectangle2 = {
		static_cast<LONG>(Position2.x - RectSize2.x),
		static_cast<LONG>(Position2.y - RectSize2.y),
		static_cast<LONG>(Position2.x + RectSize2.x),
		static_cast<LONG>(Position2.y + RectSize2.y)
	};

	Vector Result;
	IntersectRect(&Intersect, &Rectangle1, &Rectangle2);
	if (!IsRectEmpty(&Intersect)) {
		LONG iWidth, iHeight;
		LONG XAxis, YAxis;

		XAxis = YAxis = 0;

		iWidth = Intersect.right - Intersect.left;
		iHeight = Intersect.bottom - Intersect.top;

		XAxis = ((Intersect.left == Rectangle1.left) ? (1) : (-1));
		YAxis = ((Intersect.top == Rectangle1.top) ? (1) : (-1));
		
		LONG Offset = ((iWidth <= iHeight) ? (iWidth) : (iHeight));
		if (bTrue) {
			if (iWidth < iHeight) {
				OffsetRect(&Rectangle1, XAxis * Offset, 0);
				Result = Vector(Position1.x + XAxis * Offset, Position1.y);
			}
			else {
				OffsetRect(&Rectangle1, 0, YAxis * Offset);
				Result = Vector(Position1.x, Position1.y + YAxis * Offset);
			}
			// 위와 같이 하거나 닿는 면의 길이를 비교하여 미끄러지지 않게 만들 수 있다
			// OffsetRect(&Rectangle1, XAxis * Offset, YAxis * Offset);
			// Result = Vector(Rectangle1.left + RectSize1.x, Rectangle1.top + RectSize1.y);
			// Result = Vector(Position1.x + XAxis * Offset, Position1.y + YAxis * Offset);
			P1->GetOwner()->SetPosition(Result);
		}
		else {
			if (iWidth < iHeight) {
				OffsetRect(&Rectangle1, XAxis * Offset, 0);
				Result = Vector(Position1.x + XAxis * Offset, Position1.y);
			}
			else {
				OffsetRect(&Rectangle1, 0, YAxis * Offset);
				Result = Vector(Position1.x, Position1.y + YAxis * Offset);
			}
			// OffsetRect(&Rectangle2, XAxis * Offset, YAxis * Offset);
			// Result = Vector(Rectangle2.left + RectSize2.x, Rectangle2.top + RectSize2.y);
			// Result = Vector(Position2.x + XAxis * Offset, Position2.y + YAxis * Offset);
			P2->GetOwner()->SetPosition(Result);
		}
	}

	return TRUE;
}

void Collider::SetCollisionFlagLayer(COLLISION_LAYER_TYPE Layer) {
	_CollisionFlag = Layer;
}