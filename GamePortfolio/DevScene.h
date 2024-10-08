#pragma once

/*
	등장 요소를 씬마다 개별 관리한다면 지금처럼 관리 함수를 오버라이딩 하여
	필요한 처리를 해야하기 때문에 등장 요소가 많지 않다면 BaseScene에서 통합해서 관리하는 것도 좋다.
	
	만약, 개발중인 게임이 그 구조상 등장 요소의 종류가 많지 않고,
	각 종류의 개체가 최대 10만개를 넘지 않는다면, 데이터 자료 구조로 해시 테이블을 선택해 관리하는 것이 적당해 보인다.
	
	체이닝 기반의 해시 테이블 구조를 가지면 추가/삭제가 용이하고 탐색에서도 큰 문제가 없다.
	또, 이진 탐색 트리 구조로 체이닝을 구성하면 탐색에서도 최적의 성능을 낸다.
	단, 현재는 실습이 목적이므로 벡터를 활용하기로 한다.
	===================================================================================================
	UI 실습 이후 필요에 의해 BaseScene으로 모든 관리 함수를 옮겼다.
	등장 요소를 씬마다 개별 관리할 경우 불필요한 생성(초기화) 과정이 추가되며,
	리소스를 호출하는 과정에서 로직이 정상 작동하지 않기 때문에 기반 클래스에서 관리하도록 했다.
*/
class DevScene : public BaseScene
{
	using Super = BaseScene;

	HWND _hWnd;
	LONG iWidth, iHeight;

public:
	void LoadMap();
	void LoadPlayer();
	void LoadMonster();
	void LoadProjectile();
	void LoadEffect();
	void LoadTilemap();

public:
	BOOL MoveTo(Vector Position);
	Vector Convert(Vector Position);

public:
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);

public:
	DevScene();
	virtual ~DevScene();

	class TileMapActor* _TileMapActor;
};