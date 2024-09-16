#include "pch.h"

BaseScene::BaseScene(){
	
}

BaseScene::~BaseScene() {
	CleanUp();
}

BOOL BaseScene::Initialize() {
	/* 타일맵 제작을 위해 추상화 클래스를 일반 클래스로 변경 */
	
	/* 게임 시작 이후 가져야 할 자원을 최상위 클래스에서 관리한다. */
	
	for (const std::vector<Actor*>& type : _Actors) {
		for (Actor* actor : type) {
			actor->Initialize();
		}
	}

	/*Panel* GUI = CreateUIPanel<ContentsPanel>();
	AppendUIPanel(GUI);

	GUI->Initialize();*/

	return TRUE;
}

void BaseScene::Update(float dtSeconds) {

	// 충돌 처리
	std::vector<Collider*>& Colliders = _Colliders;

	for (int i = 0; i < Colliders.size(); i++) {
		for (int j = i + 1; j < Colliders.size(); j++) {
			Collider* P1, * P2;
			P1 = Colliders[i];
			P2 = Colliders[j];

			if (P1->CheckCollision(P2)) {
				// TODO:
				if (P1->GetColliderSet().contains(P2) == FALSE) {
					P1->GetOwner()->OnComponentBeginOverlap(P1, P2);
					P2->GetOwner()->OnComponentBeginOverlap(P2, P1);
					P1->GetColliderSet().insert(P2);
					P2->GetColliderSet().insert(P1);
					WindowsUtility::Trace(TEXT("Collision Occured"));
				}
			}
			else {
				if (P1->GetColliderSet().contains(P2)) {
					P1->GetOwner()->OnComponentEndOverlap(P1, P2);
					P2->GetOwner()->OnComponentEndOverlap(P2, P1);
					P1->GetColliderSet().erase(P2);
					P2->GetColliderSet().erase(P1);
					WindowsUtility::Trace(TEXT("Collision Ended"));
				}
			}
		}

		/*for (Panel* p : _GUIPanels) {
			p->Update(dtSeconds);
		}*/
	}

	// 갱신
	for (const std::vector<Actor*>& type : _Actors) {
		for (Actor* actor : type) {
			actor->Update(dtSeconds);
		}
	}
}

void BaseScene::Render(HDC hDC) {
	std::vector<Actor*>& Actors = _Actors[LAYER_OBJECT];
	std::sort(Actors.begin(), Actors.end(), [=](Actor* a, Actor* b) {
		return a->GetPosition().y < b->GetPosition().y;
	});

	for (const std::vector<Actor*>& type : _Actors) {
		for (Actor* actor : type) {
			actor->Render(hDC);
		}
	}

	/*for (Panel* p : _GUIPanels) {
		p->Render(hDC);
	}*/
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

Creature* BaseScene::GetCreatureAt(Vector TargetCellPosition) {
	/* 단순한 방법 (Big(O): n )*/
	for (Actor* A : _Actors[LAYER_OBJECT]) {
		Creature* C = dynamic_cast<Creature*>(A);
		if (C && C->GetCellPosition() == TargetCellPosition) {
			return C;
		}
	}

	return NULL;
}