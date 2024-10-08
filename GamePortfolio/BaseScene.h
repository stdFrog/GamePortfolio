#pragma once

class GameEngine;

class Actor;
class GameObject;
class Collider;

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

	std::vector<ObjectInterface*> _Objects;
	std::vector<Collider*> _Colliders;
	std::vector<Actor*> _Actors[LAYER_TYPE_LAST_COUNT];
	std::vector<Panel*> _GUIPanels;

public:
	Creature* GetCreatureAt(Vector TargetCellPosition);

public:
	template<typename T>
	T* SpawnObject(Vector NewPosition) {
		/* Type-Trait */
		auto IsGameObject = std::is_convertible_v<T*, GameObject*>;
		assert(IsGameObject);

		T* NewGameObject = new T();
		NewGameObject->SetScene(this);
		NewGameObject->SetCellPosition(NewPosition, TRUE);
		AppendActor(NewGameObject);

		NewGameObject->Initialize();

		return NewGameObject;
	}

private:
	// 씬 마다 카메라를 활용하는 방법이 다를 수 있다.
	CameraObject _MainCamera;

public:
	CameraObject& GetMainCamera() { return _MainCamera; }
	const CameraObject& GetMainCamera() const { return _MainCamera; }

public:
	const std::vector<Panel*>& GetUIPanels() { return _GUIPanels; }

	template <typename T>
	T* CreateUIPanel() {
		static_assert(std::is_convertible_v<T*, Panel*>);
		T* NewPanel = new T(this);

		return NewPanel;
	}

	BOOL AppendUIPanel(Panel*);
	BOOL RemoveUIPanel(Panel*);

public:
	const std::vector<Collider*>& GetColliders() { return _Colliders; }

	template <typename T>
	T* CreateCollider() {
		static_assert(std::is_convertible_v<T*, Collider*>);
		T* NewCollider = new T();

		return NewCollider;
	}

	BOOL AppendCollider(Collider*);
	BOOL RemoveCollider(Collider*);

public:
	const std::vector<Actor*>& GetActors() { return *_Actors; }
	const std::vector<Actor*>& GetActors(LAYER_TYPE Type) { return _Actors[Type]; }

	template <typename T>
	T* CreateActor() {
		// type trait
		static_assert(std::is_convertible_v<T*, Actor*>);

		T* NewActor = new T();
		NewActor->SetScene(this);
		NewActor->SetInitializeState(NewActor->Initialize());

		return NewActor;
	}

	BOOL AppendActor(Actor*);
	BOOL RemoveActor(Actor*);

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
	BaseScene();
	virtual ~BaseScene();

public:
	/*
		추상화 클래스로 설계하였으나 타일맵 제작을 위해 최상위 씬에서도 관리 함수를 사용하기로 한다.
	*/
	virtual void Update(float);
	virtual void Render(HDC);
	virtual BOOL Initialize();
	void* GetInstance() { return _EngineInstance; }
	void SetInstance(void* EngineInstance) { _EngineInstance = EngineInstance; }
	// void SetInputInstance(void* EngineInstance, InputManager GameEngine::* InputInstance) { _EngineInstance = EngineInstance;  _InputInstance = InputInstance; }
};

