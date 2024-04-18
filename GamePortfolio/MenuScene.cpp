#include "pch.h"
#include "MenuScene.h"

MenuScene::MenuScene() {

}

MenuScene::~MenuScene() {

}

BOOL MenuScene::Initialize() {

	return TRUE;
}

void MenuScene::Update(float dtSeconds) {
	const auto& Engine = (GameEngine*)_EngineInstance;
	auto& Input = ((GameEngine*)Engine)->GetInputManager();

	if (Input.IsPressed(InputButton::E)) {
		Engine->ChangeScene(SceneType::FortressScene);
	}
}

void MenuScene::Render(HDC hDC) {
	const auto& Engine = (GameEngine*)_EngineInstance;
	LineMesh Menu = Engine->GetLineMesh(L"Menu");

	Menu.Render(hDC, Vector(0, 0));
}
