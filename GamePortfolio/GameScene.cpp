#include "pch.h"

GameScene::GameScene() {

}

GameScene::~GameScene() {
	
}

BOOL GameScene::Initialize() {
	
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
