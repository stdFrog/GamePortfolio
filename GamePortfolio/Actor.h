#pragma once
#include "ObjectInterface.h"

// 엔진측 코드
/* 
	- Actor는 언리얼의 스타일을 따라한 위한 임시 클래스이다.

	기반 클래스로서 ObjectInterface의 모든 기능을 그대로 가져야 한다.
	그러나 현재 프로젝트에선 이미 일전에 만들어둔 객체가 있으므로
	단순 파생 클래스로 활용하기로 한다.

	씬을 구성하는 객체는 결국 ObjectInterface의 원형과 다르지 않다.
*/

class Component;
class Collider;

class Actor : public ObjectInterface
{
protected:
	LAYER_TYPE _Layer = LAYER_OBJECT;
	std::vector<Component*> _Components;

public:
	void AppendComponent(Component*);
	void RemoveComponent(Component*);

public:
	void SetLayerType(LAYER_TYPE Layer) { _Layer = Layer; }
	LAYER_TYPE GetLayerType() { return _Layer; }

public:
	virtual void OnComponentBeginOverlap(Collider*, Collider*);
	virtual void OnComponentEndOverlap(Collider*, Collider*);

public:
	Actor(ObjectType Type = ObjectType::None);
	virtual ~Actor();

	virtual BOOL Initialize();				// BeginPlay
	virtual void Update(float);				// Tick
	virtual void Render(HDC);
};

