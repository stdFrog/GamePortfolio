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

	template <typename T>
	T* CreateActor() {
		// type trait
		static_assert(std::is_convertible_v<T*, Actor*>);

		T* NewActor = new T();
		NewActor->SetScene(this);
		NewActor->SetInitializeState(NewActor->Initialize());

		return NewActor;
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

