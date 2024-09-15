#include "pch.h"
#include "Creature.h"

Creature::Creature(ObjectType Type) : GameObject(Type) {

}

Creature::~Creature() {

}

BOOL Creature::Initialize() {
	Super::Initialize();

	return TRUE;
}

void Creature::Update(float dtSeconds) {
	Super::Update(dtSeconds);

}

void Creature::Render(HDC hDC) {
	Super::Render(hDC);

}