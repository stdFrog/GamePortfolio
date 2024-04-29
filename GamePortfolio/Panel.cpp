#include "pch.h"
#include "Panel.h"

Panel::Panel(BaseScene* CurrentScene) : UI(CurrentScene){

}

Panel::~Panel() {
	for (UI* Child : _Childs) {
		delete Child;
		Child = NULL;
	}

	_Childs.clear();
}

void Panel::AddChild(UI* NewInterface) {
	if (NewInterface == NULL) {return;}

	_Childs.push_back(NewInterface);
}

BOOL Panel::RemoveChild(UI* Target) {
	auto findIt = std::find(_Childs.begin(), _Childs.end(), Target);

	if (findIt == _Childs.end()) { return FALSE; }
	_Childs.erase(findIt);
	return TRUE;
}

BOOL Panel::Initilaize() {
	Super::Initialize();
	for (UI* Child : _Childs) {
		Child->Initialize();
	}

	return TRUE;
}

void Panel::Update(float dtSeconds) {
	Super::Update(dtSeconds);

	for (UI* Child : _Childs) {
		Child->Update(dtSeconds);
	}
}

void Panel::Render(HDC hDC) {
	Super::Render(hDC);

	for (UI* Child : _Childs) {
		Child->Render(hDC);
	}
}