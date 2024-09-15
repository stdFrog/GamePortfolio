#include "pch.h"
#include "HitEffect.h"

HitEffect::HitEffect() : GameObject(ObjectType::Effect) {

}

HitEffect::~HitEffect() {

}

BOOL HitEffect::Initialize() {
	Super::Initialize();

	return TRUE;
}

void HitEffect::Update(float dtSeconds) {
	Super::Update(dtSeconds);

}

void HitEffect::Render(HDC hDC) {
	Super::Render(hDC);

}