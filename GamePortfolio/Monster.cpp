#include "pch.h"

Monster::Monster() : Creature(ObjectType::Monster){

}

Monster::~Monster() {

}

BOOL Monster::Initialize() {
	Super::Initialize();
	const auto& Scene = dynamic_cast<DevScene*>(GetScene());
	const auto& Engine = (GameEngine*)(Scene->GetInstance());

	_FlipbookMove[DIRECTION_UP] = Engine->GetFlipbook(L"FB_SnakeUp");
	_FlipbookMove[DIRECTION_DOWN] = Engine->GetFlipbook(L"FB_SnakeDown");
	_FlipbookMove[DIRECTION_LEFT] = Engine->GetFlipbook(L"FB_Snakeleft");
	_FlipbookMove[DIRECTION_RIGHT] = Engine->GetFlipbook(L"FB_SnakeRight");

	SetState(OBJECTSTATE::MOVE);
	SetState(OBJECTSTATE::IDLE);

	return TRUE;
}

void Monster::Update(float dtSeconds) {
	Super::Update(dtSeconds);

}

void Monster::Render(HDC hDC) {
	Super::Render(hDC);

}

void Monster::UpdateIdle(float dtSeconds) {

}

void Monster::UpdateMove(float dtSeconds) {

}

void Monster::UpdateSkill(float dtSeconds) {

}

void Monster::UpdateAnimation() {
	SetFlipbook(_FlipbookMove[_Direction]);
}