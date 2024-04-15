#include "pch.h"

GameScene::GameScene() {

}

GameScene::~GameScene() {
	
}

BOOL GameScene::Initialize() {
	Player* P = CreateObject<Player>();
	P->SetPosition(Vector(400, 400));
	AppendObject(P);

	for (int i = 0; i < 5; i++){
		Monster* M = CreateObject<Monster>();
		M->SetPosition(Vector((float)(i+1) * 100.f, 100.f));
		AppendObject(M);
	}	

	return TRUE;
}

void GameScene::Update(float dtSeconds) {
	// 충돌 판정
	const std::vector<ObjectInterface*> Objects = GetObjects();
	for (ObjectInterface* Target : Objects) {
		Target->Update(dtSeconds);
	}
}

void GameScene::Render(HDC hDC) {
	const std::vector<ObjectInterface*>& Objects = GetObjects();
	for (ObjectInterface* Target : Objects) {
		Target->Render(hDC);
	}
}
