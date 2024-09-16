#pragma once
// #include "FlipbookActor.h"

/*
	공통 자료이므로 StdLib.h로 복사

enum class OBJECTSTATE {
	Idle,
	Move,
	Jump,
	Skill
};
*/

/* 
	여기부터 컨텐츠 코드

	이곳에 컴포넌트 형태로 카메라 오브젝트를 설계하고 업데이트를 이용할 것인가?
	또는, 하드 코딩할 것인가에 대한 고민도 충분히 이뤄져야 한다.

	기반 클래스를 수정한 이후 Player를 세분화하여 관리할 수 있게 되었다.
	마찬가지로, Monster 역시 대상 피조물의 이름이나 종류를 구분할 수 있게 되었으며
	같은 방법으로 필요한 만큼 늘려나갈 수 있다.
*/
class Player : public Creature // FlipbookActor
{
	using Super = Creature;

	Flipbook* _FlipbookIdle[4];
	Flipbook* _FlipbookMove[4];
	Flipbook* _FlipbookAttack[4];
	Flipbook* _FlipbookBow[4];
	Flipbook* _FlipbookStaff[4];

	// OBJECTSTATE _State = OBJECTSTATE::IDLE;

	/* 작업을 나누기 위해 이런 식으로 함수 단위로 나누어 관리하는 것도 좋다. */
		/*
private:
	void UpdateInput(float);
	void UpdateGravity(float);

private:
	virtual void UpdateMoveScript(float);
	virtual void UpdateJumpScript(float);

public:
	virtual void OnComponentBeginOverlap(Collider*, Collider*);
	virtual void OnComponentEndOverlap(Collider*, Collider*);

	*/

private:
	virtual void UpdateIdle(float);
	virtual void UpdateMove(float);
	virtual void UpdateSkill(float);

	void UpdateAnimation();

private:
	BOOL _KeyPressed = FALSE;
	WEAPONTYPE _WeaponType = WEAPONTYPE::SWORD;

public:
	void SetWeaponType(WEAPONTYPE NewWeaponType) { _WeaponType = NewWeaponType; }
	WEAPONTYPE GetWeaponType() { return _WeaponType; }

public:
	Player();
	virtual ~Player();

	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};