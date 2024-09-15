#pragma once

class BaseScene;

/*
	클래스 설계를 두 단계에 거쳐 진행했다.

	처음 기술 설계부터 대표적인 등장 요소(예로, 피격 가능한 대상 또는 환경 등)를 기반 클래스로
	파생 클래스를 늘려나가는 것이 좋다.

	이번 프로젝트처럼 두 단계로 나누어 진행하면 추가 비용이 발생한다.
*/
enum class ObjectType {
	None,
	Player,
	Monster,
	Projectile,
	Effect,
	Environment
};

struct Status {
	int HP = 0;
	int MP = 0;
	int MaxHP = 0;
	int MaxMP = 0;
	int Attack = 0;
	int Defence = 0;
	float Speed = 0.f;
};

class ObjectInterface
{
	BOOL _bInitialized;

protected:
	ObjectType _Type = ObjectType::None;
	Vector _Position;
	Status _Status;
	BaseScene* _Scene;
	Transform _Transform;

public:
	ObjectType GetObjectType() { return _Type; }
	Vector GetPosition() { return _Position; }
	BaseScene* GetScene() { return _Scene; }

public:
	void SetPosition(Vector Position) { _Position = Position; }
	void SetScene(BaseScene* Scene) { _Scene = Scene; }
	void SetType(ObjectType Type) { _Type = Type; }
	void SetInitializeState(BOOL bState) { _bInitialized = bState; }

public:
	ObjectInterface(ObjectType Type = ObjectType::None);
	virtual ~ObjectInterface();

public:
	virtual BOOL Initialize() = 0;
	virtual void Update(float) = 0;
	virtual void Render(HDC) = 0;
};

