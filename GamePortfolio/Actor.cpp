#include "pch.h"
#include "Actor.h"

Actor::Actor(ObjectType Type) : ObjectInterface(Type){

}

Actor::~Actor() {

}

BOOL Actor::Initialize() {
	return TRUE;
}

void Actor::Update(float dtSeconds) {

}

void Actor::Render(HDC hDC) {

}