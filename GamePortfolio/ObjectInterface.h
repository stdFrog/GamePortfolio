#pragma once

class BaseScene;

enum class ObjectType {
	None,
	Player,
	Monster,
	Projectile,
	Environment
};

struct Status {
	int HP = 0;
	int MP = 0;
	int MaxHP = 0;
	int MaxMP = 0;
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

public:
	ObjectType GetObjectType() { return _Type; }
	Vector GetPosition() { return _Position; }
	void SetPosition(Vector Position) { _Position = Position; }
	void SetScene(BaseScene* Scene) { _Scene = Scene; }
	void SetInitializeState(BOOL bState) { _bInitialized = bState; }

public:
	ObjectInterface(ObjectType Type = ObjectType::None);
	virtual ~ObjectInterface();

public:
	virtual BOOL Initialize() = 0;
	virtual void Update(float) = 0;
	virtual void Render(HDC) = 0;
};

