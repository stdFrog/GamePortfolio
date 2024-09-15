#include "pch.h"
#include "Arrow.h"

Arrow::Arrow() : Projectile() {

}

Arrow::~Arrow() {

}

BOOL Arrow::Initialize() {
	Super::Initialize();

	return TRUE;
}

void Arrow::Update(float dtSeconds) {
	Super::Update(dtSeconds);

}

void Arrow::Render(HDC hDC) {
	Super::Render(hDC);

}