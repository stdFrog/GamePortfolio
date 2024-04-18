#include "pch.h"

GameEngine::GameEngine(){

}

GameEngine::~GameEngine() {
    
}

BOOL GameEngine::LoadResources() {
    // TODO : Mesh, Texture, Sprite Load
    CreateLineMesh(L"Player", L"LineUnit.txt");
    CreateLineMesh(L"UI", L"UI.txt");
    CreateLineMesh(L"Menu", L"Menu.txt");
    CreateLineMesh(L"MissileTank", L"MissileTank.txt");
    CreateLineMesh(L"CanonTank", L"CanonTank.txt");

    return TRUE;
}

BOOL GameEngine::Initialize(HWND hWnd) {
    if (!_bSceneReady) {
        _bSceneReady = ChangeScene(SceneType::MenuScene);
    }

    if (!_bInputInitialized) {
        _bInputInitialized = _InputManager.Initialize(hWnd);
    }
    
    if (!_bResourceReady) {
        _bResourceReady = LoadResources();
    }

    _bAllInitialized = (_bSceneReady && _bInputInitialized && _bResourceReady);
	return ((_bAllInitialized) ? (_hMainWnd = hWnd, TRUE) : FALSE);
}

void GameEngine::Update(float dtSeconds) {
    if (!_bInputInitialized) { return; }

    _MainScene->Update(dtSeconds);
}

void GameEngine::Render(HDC hDC) {
    if (!_bSceneReady) { return; }

    _MainScene->Render(hDC);
}

BOOL GameEngine::ChangeScene(SceneType NewSceneType) {
    if (NewSceneType == _CurrentScene) { return FALSE; }

    BaseScene* _NewScene = NULL;

    switch (NewSceneType) {
    case SceneType::DevScene:
        _NewScene = new DevScene();
        break;

    case SceneType::GameScene:
        _NewScene = new GameScene();
        break;

    case SceneType::EditScene:
        _NewScene = new EditScene();
        break;

    case SceneType::MenuScene:
        _NewScene = new MenuScene();
        break;

    case SceneType::FortressScene:
        _NewScene = new FortressScene();
        break;
    }

    _MainScene.reset(_NewScene);
    _CurrentScene = NewSceneType;
    _MainScene->SetInstance(this);
    // _MainScene->SetInputInstance(this, &GameEngine::_InputManager);

    return _MainScene->Initialize();
}

void GameEngine::CreateLineMesh(const std::wstring& Name, const std::wstring& Path) {
    LineMesh* Append = new LineMesh;
    Append->Load(Path);
    _LineMeshes[Name].reset(Append);
}