#pragma once

class Actor;
class GameObject;
class Collider;
class UI;

/*
	등장 요소를 씬마다 개별 관리한다면 지금처럼 관리 함수를 오버라이딩 하여
	필요한 처리를 해야하기 때문에 등장 요소가 많지 않다면 BaseScene에서 통합해서 관리하는 것도 좋다.
	
	다만, 속도의 저하는 감수해야 한다.
	만약, 개발중인 게임이 그 구조상 등장 요소의 종류가 많지 않고,
	각 종류의 개체가 최대 10만개를 넘지 않는다면, 데이터 자료 구조로 해시 테이블을
	선택해 관리하는 것이 적당해 보인다.
	
	체이닝 기반의 해시 테이블 구조를 가지면 추가/삭제가 용이하고 탐색에서도 큰 문제가 없다.
	또, 이진 탐색 트리 구조로 체이닝을 구성하면 탐색에서도 최적의 성능을 낸다.
	단, 현재는 실습이 목적이므로 벡터를 활용하기로 한다.
*/
class DevScene : public BaseScene
{
	std::vector<Actor*> _Actors[LAYER_TYPE_LAST_COUNT];
	std::vector<Collider*> _Colliders;
	//std::vector<Actor*> _Actors;
	// 일반적으로 Actor나 오브젝트로 분리하지 않고 씬 내부에서 관리하는 객체로 생성하여
	// 필요할 때만 호출해 사용한다.
	std::vector<UI*> _UserInterfaces;

	HWND _hWnd;
	LONG iWidth, iHeight;

public:
	template <typename T>
	T* CreateCollider() {
		static_assert(std::is_convertible_v<T*, Collider*>);
		T* NewCollider = new T();

		return NewCollider;
	}

	BOOL AppendCollider(Collider*);
	BOOL RemoveCollider(Collider*);

public:
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
	void CleanUp();

public:
	DevScene();
	virtual ~DevScene();

public:
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};