#include "pch.h"
#include "Actor.h"
#include "Component.h"

Actor::Actor(ObjectType Type) : ObjectInterface(Type){

}

Actor::~Actor() {
	std::for_each(_Components.begin(), _Components.end(), [=](Component* Remove) {delete Remove; });
	_Components.clear();
}

BOOL Actor::Initialize() {
	for (Component* comp : _Components) {
		comp->Initialize();
	}

	return TRUE;
}

void Actor::Update(float dtSeconds) {
	for (Component* comp : _Components) {
		comp->Update(dtSeconds);
	}
}

void Actor::Render(HDC hDC) {
	for (Component* comp : _Components) {
		comp->Render(hDC);
	}
}

void Actor::AppendComponent(Component* NewComponent) {
	if (NewComponent == NULL) { return; }

	auto it = std::find(_Components.begin(), _Components.end(), NewComponent);
	if (it != _Components.end()) { return; }

	NewComponent->SetOwner(this);
	_Components.push_back(NewComponent);
}

void Actor::RemoveComponent(Component* Target) {
	auto findIt = std::find(_Components.begin(), _Components.end(), Target);

	if (findIt == _Components.end()) { return; }
	_Components.erase(findIt);
}