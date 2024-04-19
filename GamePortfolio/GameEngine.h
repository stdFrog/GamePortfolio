#pragma once
// {Scene | 0 < Scene <= x := MainScene(1)}

class GameEngine
{
    HWND _hMainWnd = NULL;
    BOOL _bSceneReady = FALSE;
    BOOL _bMeshReady = FALSE;
    BOOL _bTextureReady = FALSE;
    BOOL _bResourceReady = FALSE;
    BOOL _bInputInitialized = FALSE;
    BOOL _bAllInitialized = FALSE;
private:
    /*
        장면이 하나라면 등장 요소만으로 구성해도 상관없다.

        더 정확히는 게임 전반에 이르러 규칙이 하나로 통용된다면
        즉, 컨트롤러나 게임 모드/규칙 등에서 변경될 요소가 전혀 없다면
        번거롭게 Scene이라는 개념을 추가할 필요가 없다.

        깊이 버퍼를 직접 만들어 사용하게 되면 꽤 번거로울 수 있다.
    */
    std::unique_ptr<BaseScene> _MainScene;
    SceneType _CurrentScene = SceneType::None;

public:
    BOOL ChangeScene(SceneType NewSceneType);

public:
    std::unique_ptr<BaseScene>& GetCurrentScene() { return _MainScene; }
    const std::unique_ptr<BaseScene>&  GetCurrentScene() const { return _MainScene;}

private:
    InputManager _InputManager;

public:
    BOOL IsInputInitialized() const { return _bInputInitialized; }
    InputManager& GetInputManager() { return _InputManager; }
    const InputManager& GetInputManager() const { return _InputManager; }

private:
    // 간단한 메시
    std::unordered_map<std::wstring, std::unique_ptr<LineMesh>> _LineMeshes;
    
public:
    void CreateLineMesh(const std::wstring& Name, const std::wstring& Path);
    LineMesh& GetLineMesh(const std::wstring& Name) { return *_LineMeshes.at(Name).get(); }
    const LineMesh& GetLineMesh(const std::wstring& Name) const { return *_LineMeshes.at(Name).get(); }

    // TODO :
    // Mesh, Camera, Texture, Input, GameObject, Load Resources
   /* bool _IsInitialized = false;
    CameraObject _MainCamera;

    std::unordered_map<std::size_t, std::unique_ptr<Mesh>> _Meshes;
    std::unordered_map<std::size_t, std::unique_ptr<Texture>> _Textures;
    std::unordered_map<std::string, GameObject*> _BoneGameObjectPtrs;
    */

public:
    GameEngine();
    ~GameEngine();

public:
    /* Scene 개념이 필요없다면 굳이 Update, Render 함수를 만들 필요가 없다. */
    /* 게임 엔진으로 사용할 거라면 이런 Scene 보단 확장을 위해 CanvasWinodw 따위를 만드는 것이 더 좋다. */
    void Update(float);
    void Render(HDC);

public:
    BOOL Initialize(HWND);
    BOOL LoadResources();
    BOOL IsInitialized() const { return _bAllInitialized; }
};
