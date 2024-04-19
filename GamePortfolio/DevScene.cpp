#include "pch.h"
#include "Texture.h"
#include "Sprite.h"

DevScene::DevScene() {
	
}

DevScene::~DevScene() {

}

BOOL DevScene::Initialize() {
	// 엔진에서 공용으로 관리할 이미지 리소스를 관리하고
	// 씬에서는 해당 씬에서 사용할 것만 호출해서 사용하고 해제하고 반복
	const auto& Engine = (GameEngine*)_EngineInstance;

	Engine->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
	// Engine->LoadTexture(L"Sword", L"Sprite\\Item\\Sword.bmp");
	Engine->LoadTexture(L"Potion", L"Sprite\\UI\\Mp.bmp");
	Engine->LoadTexture(L"PlayerDown", L"Sprite\\Player\\PlayerDown.bmp", RGB(128, 128, 128));
	Engine->LoadTexture(L"PlayerUp", L"Sprite\\Player\\PlayerUp.bmp", RGB(128, 128, 128));
	Engine->LoadTexture(L"PlayerLeft", L"Sprite\\Player\\PlayerLeft.bmp", RGB(128, 128, 128));
	Engine->LoadTexture(L"PlayerRight", L"Sprite\\Player\\PlayerRight.bmp", RGB(128, 128, 128));
	Engine->LoadTexture(L"Start", L"Sprite\\UI\\Start.bmp");
	Engine->LoadTexture(L"Edit", L"Sprite\\UI\\Edit.bmp");
	Engine->LoadTexture(L"Exit", L"Sprite\\UI\\Exit.bmp");

	Texture* Temp = Engine->GetTexture(L"Start");
	Engine->CreateSprite(L"Start_On", Temp, 150, 0, 150, 150);

	_hWnd = GetForegroundWindow();
	WindowsUtility::GetWindowSize(_hWnd, &iWidth, &iHeight);

	return TRUE;
}

void DevScene::Update(float dtSeconds) {
	
}

void DevScene::Render(HDC hDC) {
	const auto& Engine = (GameEngine*)_EngineInstance;
	// Texture* texture = Engine->GetTexture(L"Stage01");
	Sprite* sprite = Engine->GetSprite(L"Start_On");

	// BOOL bRepaint = Engine->GetOnResizeState();
	// if (bRepaint) { WindowsUtility::GetWindowSize(_hWnd, &iWidth, &iHeight); }

	BitBlt(hDC, 0, 0, iWidth, iHeight, sprite->GetSpriteDC(), sprite->GetPosition().x, sprite->GetPosition().y, SRCCOPY);
}