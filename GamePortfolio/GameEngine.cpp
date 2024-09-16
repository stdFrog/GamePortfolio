#include "pch.h"

GameEngine::GameEngine(){

}

GameEngine::~GameEngine() {
    for (auto& T : _Textures) {
        delete T.second;
        T.second = NULL;
    }

    _Textures.clear();

    for (auto& S : _Sprites) {
        delete S.second;
        S.second = NULL;
    }

    _Sprites.clear();

    for (auto& F : _Flipbooks) {
        delete F.second;
        F.second = NULL;
    }

    _Flipbooks.clear();

    for (auto& M : _TileMaps) {
        delete M.second;
        M.second = NULL;
    }

    _TileMaps.clear();

    /*
    for (auto& N : _Sounds) {
        delete N.second;
        N.second = NULL;
    }

    _Sounds.clear();
    */
}

/*
Texture& GameEngine::CreateTexture(const std::wstring& Hash, const std::wstring& Path) {
    auto Temp = std::make_unique<Texture>()->LoadBmp(_hMainWnd, Path);
    _Textures.insert({ Hash, std::move(Temp) });
    return *_Textures.at(Hash).get();
}
*/

TileMap* GameEngine::CreateTileMap(const std::wstring& Hash) {
    if (_TileMaps.find(Hash) != _TileMaps.end()) { return _TileMaps[Hash]; }

    TileMap* NewTileMap = new TileMap();
    _TileMaps[Hash] = NewTileMap;

    return NewTileMap;
}

TileMap* GameEngine::LoadTileMap(const std::wstring& Hash, const std::wstring& Path) {
    TileMap* M = NULL;
    if (_TileMaps.find(Hash) == _TileMaps.end()) {
        _TileMaps[Hash] = new TileMap();
    }

    M = _TileMaps[Hash];

    std::filesystem::path AbsPath = _ResourcePath / Path;
    M->LoadFile(AbsPath);

    return M;
}

void GameEngine::SaveTileMap(const std::wstring& Hash, const std::wstring& Path) {
    TileMap* M = GetTileMap(Hash);

    std::filesystem::path AbsPath = _ResourcePath / Path;
    M->SaveFile(AbsPath);
}

Texture* GameEngine::LoadTexture(const std::wstring& Hash, const std::wstring& Path, int Transparent) {
    // 이미지 불러오고 해쉬로 저장
    if (_Textures.find(Hash) != _Textures.end()) {
        return _Textures[Hash];
    }

    std::filesystem::path FullPath = _ResourcePath / Path;

    Texture* NewTexture = new Texture();
    NewTexture->LoadBmp(_hMainWnd, FullPath.c_str());
    NewTexture->SetTransParent(Transparent);
    _Textures[Hash] = NewTexture;

    return NewTexture;
}

Sprite* GameEngine::CreateSprite(const std::wstring& Hash, Texture* texture, int x, int y, int cx, int cy) {
    if (_Sprites.find(Hash) != _Sprites.end()) {
        return _Sprites[Hash];
    }

    if (cx == 0) {
        cx = static_cast<int>(texture->GetSize().x);
    }

    if (cy == 0) {
        cy = static_cast<int>(texture->GetSize().y);
    }

    Sprite* NewSprite = new Sprite(texture, x, y, cx, cy);
    _Sprites[Hash] = NewSprite;

    return NewSprite;
}

Flipbook* GameEngine::CreateFlipbook(const std::wstring& Hash) {
    if (_Flipbooks.find(Hash) != _Flipbooks.end()) {
        return _Flipbooks[Hash];
    }

    Flipbook* NewFlipbook = new Flipbook();
    _Flipbooks[Hash] = NewFlipbook;
    return NewFlipbook;
}

BOOL GameEngine::LoadResources() {
    // TODO : Mesh, Texture, Sprite Load
    // ResourceManager::GetInstance()->Init(hWnd, Path);

    TCHAR Temp[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, Temp);
    lstrcat(Temp, TEXT("\\..\\Resources\\"));
    _ResourcePath = std::filesystem::path(Temp);

    return TRUE;
}

BOOL GameEngine::Initialize(HWND hWnd /*, std::filepath::path ResourcePath*/) {
    if (_hMainWnd == NULL) {
        _hMainWnd = hWnd;
    }

    if (!_bResourceReady) {
        _bResourceReady = LoadResources();
    }
    
    if (!_bInputInitialized) {
        _bInputInitialized = _InputManager.Initialize(hWnd);
    }

    if (!_bSceneReady) {
        _bSceneReady = ChangeScene(SceneType::DevScene);
    }

    /*
        SoundManager->GetInstance()->Init(hWnd);
    */

    _bAllInitialized = (_bSceneReady && _bInputInitialized && _bResourceReady);
    return _bAllInitialized;
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
    }

    _MainScene.reset(_NewScene);
    _CurrentScene = NewSceneType;
    _MainScene->SetInstance(this);
    // _MainScene->SetInputInstance(this, &GameEngine::_InputManager);

    return _MainScene->Initialize();
}

/*
    Sound* GameEngine::LoadSound(const std::wstring& Hash, const std::wstring& Path){
        if(_Sounds.find(Hash) != _Sounds.end()){
            return _Sounds[Hash];
        }

        std::filesystem::path AbsPath = _ResourcePath / Path;
        
        Sound* NewSound = new Sound();
        NewSound->LoadWave(AbsPath);
        _Sounds[Hash] = NewSound;

        return NewSound;
    }
*/