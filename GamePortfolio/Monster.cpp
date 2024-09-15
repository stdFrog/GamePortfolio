#include "pch.h"

Monster::Monster() : Creature(ObjectType::Monster){

}

Monster::~Monster() {

}

BOOL Monster::Initialize() {
	Super::Initialize();

	return TRUE;
}

void Monster::Update(float dtSeconds) {
	Super::Update(dtSeconds);

}

void Monster::Render(HDC hDC) {
	Super::Render(hDC);

}