#include "pch.h"

Monster::Monster(ObjectType Type) : ObjectInterface(ObjectType::Monster){

}

Monster::~Monster() {

}

BOOL Monster::Initialize() {
	_Status.MaxHP = 100;
	_Status.HP = 100;
	_Status.Speed = 500.f;

	return TRUE;
}

void Monster::Update(float dtSeconds) {

}

void Monster::Render(HDC hDC) {
	WindowsUtility::DrawRect(hDC, _Position, 50, 50);
}