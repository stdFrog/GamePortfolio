#pragma once

class GameEngine;

enum class SceneType {
	None,
	DevScene,
	GameScene,
	EditScene,
	LobiScene,

	LastScene,
	LAST_SCENE_COUNT = LastScene
};

class BaseScene
{
protected:
	void* _EngineInstance;
	InputManager GameEngine::* _InputInstance;
	std::vector<ObjectInterface*> _Objects;				// 각 씬에 개별 배치할 것인가?

private:
	// 씬 마다 카메라를 활용하는 방법이 다를 수 있다.
	CameraObject _MainCamera;

public:
	CameraObject& GetMainCamera() { return _MainCamera; }
	const CameraObject& GetMainCamera() const { return _MainCamera; }

public:
	BaseScene();
	virtual ~BaseScene();

public:
	const std::vector<ObjectInterface*>& GetObjects() { return _Objects; }

	template <typename T>
	T* CreateObject() {
		// type trait
		static_assert(std::is_convertible_v<T*, ObjectInterface*>);

		T* NewObject = new T();
		NewObject->SetScene(this);
		NewObject->SetInitializeState(NewObject->Initialize());

		return NewObject;
	}

	BOOL AppendObject(ObjectInterface*);
	BOOL RemoveObject(ObjectInterface*);
	void CleanUp();

public:
	virtual void Update(float) = 0;
	virtual void Render(HDC) = 0;
	virtual BOOL Initialize() = 0;
	void* GetInstance() { return _EngineInstance; }
	void SetInstance(void* EngineInstance) { _EngineInstance = EngineInstance; }
	// void SetInputInstance(void* EngineInstance, InputManager GameEngine::* InputInstance) { _EngineInstance = EngineInstance;  _InputInstance = InputInstance; }
};

