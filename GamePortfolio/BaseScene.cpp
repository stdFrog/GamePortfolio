#include "pch.h"

BaseScene::BaseScene(){
	
}

BaseScene::~BaseScene() {
	CleanUp();
}

void BaseScene::CleanUp() {
	std::for_each(_Objects.begin(), _Objects.end(), [=](ObjectInterface* Remove) {delete Remove; });
	_Objects.clear();

	for (int i = 0; i < _Actors->size(); i++) {
		for (int j = 0; j < _Actors[i].size(); j++) {
			delete _Actors[i][j];
		}
		_Actors[i].clear();
	}

	std::for_each(_Colliders.begin(), _Colliders.end(), [=](Collider* Remove) {delete Remove; });
	_Colliders.clear();

	std::for_each(_GUIPanels.begin(), _GUIPanels.end(), [=](Panel* Remove) {delete Remove; });
	_GUIPanels.clear();
}

BOOL BaseScene::AppendObject(ObjectInterface *NewObject) {
	if (NewObject == NULL) { return FALSE; }

	auto it = std::find(_Objects.begin(), _Objects.end(), NewObject);
	if (it != _Objects.end()) {
		return FALSE;
	}

	_Objects.push_back(NewObject);

	return TRUE;
}

BOOL BaseScene::RemoveObject(ObjectInterface *Target) {
	if (Target == NULL) { return FALSE; }

	auto it = std::remove(_Objects.begin(), _Objects.end(), Target);
	_Objects.erase(it, _Objects.end());

	delete Target;

	return TRUE;
}

BOOL BaseScene::AppendActor(Actor* NewObject) {
	if (NewObject == NULL) { return FALSE; }

	int type = NewObject->GetLayerType();
	for (int i = 0; i < _Actors[type].size(); i++) {
		if (NewObject == _Actors[type][i]) { return FALSE; }
	}

	_Actors[NewObject->GetLayerType()].push_back(NewObject);

	return TRUE;
}

BOOL BaseScene::RemoveActor(Actor* Target) {
	if (Target == NULL) { return FALSE; }

	// vector<Actor*>& V = _Actors[Target->GetLayerType()];
	// std::erase(std:;remove(V.begin(), V.end(), Target), V.end());

	int type = Target->GetLayerType();
	for (int i = 0; i < _Actors[type].size(); i++) {
		if (Target == _Actors[type][i]) { delete _Actors[type][i]; return TRUE; }
	}

	return FALSE;
}

BOOL BaseScene::AppendCollider(Collider* NewCollider) {
	auto it = std::find(_Colliders.begin(), _Colliders.end(), NewCollider);
	if (it != _Colliders.end()) { return FALSE; }

	_Colliders.push_back(NewCollider);
	return TRUE;
}

BOOL BaseScene::RemoveCollider(Collider* Target) {
	auto findIt = std::find(_Colliders.begin(), _Colliders.end(), Target);

	if (findIt == _Colliders.end()) { return FALSE; }
	_Colliders.erase(findIt);

	return TRUE;
}

BOOL BaseScene::AppendUIPanel(Panel* NewPanel) {
	auto it = std::find(_GUIPanels.begin(), _GUIPanels.end(), NewPanel);
	if (it != _GUIPanels.end()) { return FALSE; }

	_GUIPanels.push_back(NewPanel);
	return TRUE;
}

BOOL BaseScene::RemoveUIPanel(Panel* Target) {
	auto findIt = std::find(_GUIPanels.begin(), _GUIPanels.end(), Target);

	if (findIt == _GUIPanels.end()) { return FALSE; }
	_GUIPanels.erase(findIt);

	return TRUE;
}