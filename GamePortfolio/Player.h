#pragma once
#include "FlipbookActor.h"

/* 여기부터 컨텐츠 코드

	이곳에 컴포넌트 형태로 카메라 오브젝트를 설계하고 업데이트를 이용할 것인가?
	또는, 하드 코딩할 것인가에 대한 고민도 충분히 이뤄져야 한다.
*/
class Player : public FlipbookActor
{
	using Super = FlipbookActor;

	Flipbook* _FlipbookUp = NULL;
	Flipbook* _FlipbookDown = NULL;
	Flipbook* _FlipbookLeft = NULL;
	Flipbook* _FlipbookRight = NULL;

public:
	virtual void OnComponentBeginOverlap(Collider*, Collider*);
	virtual void OnComponentEndOverlap(Collider*, Collider*);

public:
	Player();
	virtual ~Player();

	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};

