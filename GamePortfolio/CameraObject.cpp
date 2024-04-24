#include "pch.h"
#include "CameraObject.h"

CameraObject::CameraObject() {

}

CameraObject::~CameraObject() {

}

Matrix CameraObject::GetViewMatrix() {
	return  Matrix(
		Vector::UnitX,
		Vector::UnitY,
		Vector(-_Transform.GetPosition())
		);
}