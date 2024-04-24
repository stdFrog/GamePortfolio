#include "pch.h"
#include "Transform.h"

Transform::Transform() {

}

Transform::~Transform() {

}

void Transform::Update() {
	float fsin, fcos;

	GameMath::GetSinCos(fsin, fcos, _Rotation);

	// 로컬 공간의 X축과 Y축만 관리한다.
	_Right = Vector(fcos, fsin);
	_Up = Vector(-fsin, fcos);
}

Matrix Transform::GetModelingMatrix() const {
	return Matrix(
		Vector(_Scale.x * _Right.x, _Scale.x * _Right.y, 0.f),
		Vector(_Scale.y * _Up.x, _Scale.y * _Up.y, 0.f),
		Vector(_Position.x , _Position.y, 1.f)
	);
}