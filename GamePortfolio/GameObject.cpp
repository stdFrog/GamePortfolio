#include "pch.h"
#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() {

}

GameObject::~GameObject() {

}

BOOL GameObject::Initialize() {
	for (Component* comp : _Components) {
		comp->Initialize();
	}

	return TRUE;
}

void GameObject::Update(float dtSeconds) {
	for (Component* comp : _Components) {
		comp->Update(dtSeconds);
	}
}

void GameObject::Render(HDC hDC) {
	for (Component* comp : _Components) {
		comp->Render(hDC);
	}
}

void GameObject::AddComponent(Component* Other) {
	_Components.push_back(Other);
}