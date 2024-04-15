#include "pch.h"

BaseScene::BaseScene(){
	
}

BaseScene::~BaseScene() {
	CleanUp();
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

void BaseScene::CleanUp() {
	std::for_each(_Objects.begin(), _Objects.end(), [=](ObjectInterface* Remove) {delete Remove; });
	_Objects.clear();
}