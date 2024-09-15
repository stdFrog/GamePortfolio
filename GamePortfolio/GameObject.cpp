#include "pch.h"
#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(ObjectType Type) : FlipbookActor(Type) {

}

GameObject::~GameObject() {

}

/*
void GameObject::AppendComponent(Component* Other) {
	_Components.push_back(Other);
}
*/

BOOL GameObject::Initialize() {
	Super::Initialize();

	/*
	for (Component* comp : _Components) {
		comp->Initialize();
	}
	*/

	return TRUE;
}

void GameObject::Update(float dtSeconds) {
	Super::Update(dtSeconds);

	/*
	for (Component* comp : _Components) {
		comp->Update(dtSeconds);
	}
	*/
}

void GameObject::Render(HDC hDC) {
	Super::Render(hDC);
	/*
	for (Component* comp : _Components) {
		comp->Render(hDC);
	}
	*/
}


void GameObject::SetState(OBJECTSTATE State) {
	if (_State == State) { return; }
	_State = State;
	UpdateAnimation();
}

void GameObject::SetDirection(DIRECTION Direction) {
	_Direction = Direction;
	UpdateAnimation();
}

BOOL GameObject::HasReachedDest() {
	Vector Dist = _Destination - _Position;
	return Dist.length() < 10.f;
}

BOOL GameObject::MoveTo(Vector Position) {
	const auto& Scene = dynamic_cast<DevScene*>(GetScene());
	const auto& Engine = (GameEngine*)Scene->GetInstance();
	auto& Input = Engine->GetInputManager();

	if (Scene == NULL) { return FALSE; }
	return Scene->MoveTo(Position);
}

void GameObject::SetCellPosition(Vector Position, BOOL Teleport) {
	_CellPosition = Position;

	const auto& Scene = dynamic_cast<DevScene*>(GetScene());
	if (Scene == NULL) { return; }

	_Destination = Scene->Convert(_CellPosition);
	if (Teleport) { _Position = _Destination; }
}