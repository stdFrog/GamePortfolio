#pragma once
#include "FlipbookActor.h"

enum class PlayerState {
	Idle,
	Move,
	Jump,
	Skill
};

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

	PlayerState _State = PlayerState::Jump;

	/* 작업을 나누기 위해 이런 식으로 함수 단위로 나누어 관리하는 것도 좋다. */

	void SetState(PlayerState State) { _State = State; }
	PlayerState GetState() { return _State; }

private:
	void UpdateInput(float);
	void UpdateGravity(float);
	virtual void UpdateMoveScript(float);
	virtual void UpdateJumpScript(float);

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

