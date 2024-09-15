#include "pch.h"
#include "Projectile.h"

Projectile::Projectile() : GameObject(ObjectType::Projectile) {

}

Projectile::~Projectile() {

}

BOOL Projectile::Initialize() {
	Super::Initialize();

	return TRUE;
}

void Projectile::Update(float dtSeconds) {
	Super::Update(dtSeconds);


}

void Projectile::Render(HDC hDC) {
	Super::Render(hDC);

}