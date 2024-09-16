#include "pch.h"
#include "Player.h"
#include "Flipbook.h"
#include "CameraComponent.h"

//BOOL bOnGround;

/*
	BOOL 타입의 변수를 여럿 유지할 경우 로직이 꼬일 수 있다.

	따라서, State 패턴에 따라 상태값을 유지 관리하기로 한다.
*/
Vector S(200.f,200.f), G(1000.f, 1000.f);

Player::Player() : Creature(ObjectType::Player) {
	for (int i = 0; i < 4; i++) {
		_FlipbookIdle[i] = 0;
		_FlipbookMove[i] = 0;
		_FlipbookAttack[i] = 0;
	}
}

Player::~Player() {

}

BOOL Player::Initialize() {
	Super::Initialize();
	
	const auto& Scene = dynamic_cast<DevScene*>(GetScene());
	const auto& Engine = (GameEngine*)(Scene->GetInstance());

	_FlipbookIdle[DIRECTION_UP] = Engine->GetFlipbook(L"FB_IdleUp");
	_FlipbookIdle[DIRECTION_DOWN] = Engine->GetFlipbook(L"FB_IdleDown");
	_FlipbookIdle[DIRECTION_LEFT] = Engine->GetFlipbook(L"FB_IdleLeft");
	_FlipbookIdle[DIRECTION_RIGHT] = Engine->GetFlipbook(L"FB_IdleRight");

	_FlipbookMove[DIRECTION_UP] = Engine->GetFlipbook(L"FB_MoveUp");
	_FlipbookMove[DIRECTION_DOWN] = Engine->GetFlipbook(L"FB_MoveDown");
	_FlipbookMove[DIRECTION_LEFT] = Engine->GetFlipbook(L"FB_MoveLeft");
	_FlipbookMove[DIRECTION_RIGHT] = Engine->GetFlipbook(L"FB_MoveRight");

	_FlipbookAttack[DIRECTION_UP] = Engine->GetFlipbook(L"FB_AttackUp");
	_FlipbookAttack[DIRECTION_DOWN] = Engine->GetFlipbook(L"FB_AttackDown");
	_FlipbookAttack[DIRECTION_LEFT] = Engine->GetFlipbook(L"FB_AttackLeft");
	_FlipbookAttack[DIRECTION_RIGHT] = Engine->GetFlipbook(L"FB_AttackRight");

	_FlipbookBow[DIRECTION_UP] = Engine->GetFlipbook(L"FB_BowUp");
	_FlipbookBow[DIRECTION_DOWN] = Engine->GetFlipbook(L"FB_BowDown");
	_FlipbookBow[DIRECTION_LEFT] = Engine->GetFlipbook(L"FB_BowLeft");
	_FlipbookBow[DIRECTION_RIGHT] = Engine->GetFlipbook(L"FB_BowRight");

	_FlipbookStaff[DIRECTION_UP] = Engine->GetFlipbook(L"FB_StaffUp");
	_FlipbookStaff[DIRECTION_DOWN] = Engine->GetFlipbook(L"FB_StaffDown");
	_FlipbookStaff[DIRECTION_LEFT] = Engine->GetFlipbook(L"FB_StaffLeft");
	_FlipbookStaff[DIRECTION_RIGHT] = Engine->GetFlipbook(L"FB_StaffRight");

	CameraComponent* Camera = new CameraComponent();
	AppendComponent(Camera);

	SetState(OBJECTSTATE::MOVE);
	SetState(OBJECTSTATE::IDLE);

	return TRUE;
}

void Player::Update(float dtSeconds) {
	Super::Update(dtSeconds);

	/*
	switch (_State) {
	case OBJECTSTATE::IDLE:
		UpdateIdle(dtSeconds);
		break;

	case OBJECTSTATE::MOVE:
		UpdateMove(dtSeconds);
		break;

	case OBJECTSTATE::SKILL:
		UpdateSkill(dtSeconds);
		break;
	}*/

	/*UpdateGravity(dtSeconds);
	UpdateInput(dtSeconds);

	switch (GetState()) {
	case OBJECTSTATE::Move:
		UpdateMoveScript(dtSeconds);
		break;

	case OBJECTSTATE::Jump:
		UpdateJumpScript(dtSeconds);
		break;
	}*/
	
	/*
		단순히 벡터만을 사용할 때 다음과 같이 입력을 받아 이동 시킬 수 있다.

		이 경우엔 카메라의 위치도 직접 변경해야 하는데, 대부분 컴포넌트를 만들어 이어 붙이는 편이다.
	*/
	/*const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	const auto& Engine = (GameEngine*)(Scene->GetInstance());
	auto& Input = Engine->GetInputManager();

	if (Input.IsPressed(InputButton::W)) {
		_Position.y -= S.y * dtSeconds;
		SetFlipbook(_FlipbookUp);
	}
	else if (Input.IsPressed(InputButton::S)) {
		_Position.y += S.y * dtSeconds;
		SetFlipbook(_FlipbookDown);
	} 
	else if (Input.IsPressed(InputButton::A)) {
		_Position.x -= S.x * dtSeconds;
		SetFlipbook(_FlipbookLeft);
	}
	else if (Input.IsPressed(InputButton::D)) {
		_Position.x += S.x * dtSeconds;
		SetFlipbook(_FlipbookRight);
	}*/

	/*
		행렬과 트랜스폼 정보를 이용할 때
		BOOL Up, Down, Left, Right, Space;
		Up = Input.IsPressed(InputButton::W);
		Down = Input.IsPressed(InputButton::S);
		Left = Input.IsPressed(InputButton::A);
		Right = Input.IsPressed(InputButton::D);
		Space = Input.IsPressed(InputButton::SpaceBar);

		float XAxis = 0.f, YAxis = 1.f; // 0.f;

		if (Up ^ Down) {
			YAxis = ((Up) ? (SetFlipbook(_FlipbookUp), -1.f) : (SetFlipbook(_FlipbookDown), 1.f));
		}

		if (Left ^ Right) {
			XAxis = ((Left) ? (SetFlipbook(_FlipbookLeft), -1.f) : (SetFlipbook(_FlipbookRight), 1.f));
		}

		_Transform.AddPosition(Vector(XAxis, YAxis, 1.f).GetNormalize() * Speed * dtSeconds);
		Transform& Camera = Scene->GetMainCamera().GetTransform();
		_Position = _Transform.GetPosition();
		Vector CameraPosition = Camera.GetPosition();
	*/
}

void Player::Render(HDC hDC) {
	Super::Render(hDC);

	/*
		행렬과 트랜스폼 정보를 이용할 때
		
		const auto& Scene = dynamic_cast<DevScene*>(_Scene);
		Matrix ViewMatrix = Scene->GetMainCamera().GetViewMatrix();
		Matrix S = ViewMatrix * _Transform.GetModelingMatrix();
	*/
}
/*
void Player::OnComponentBeginOverlap(Collider* I, Collider* Target) {
	SetState(OBJECTSTATE::Move);
	S = Vector(200.f, 200.f);
}

void Player::OnComponentEndOverlap(Collider* I, Collider* Target) {
	SetState(OBJECTSTATE::Jump);
}

void Player::UpdateGravity(float dtSeconds) {
	if (GetState() == OBJECTSTATE::Move) { return; }
	S.y += G.y * dtSeconds;
	_Position.y += S.y * dtSeconds;
}

특수 상황이 아닌 일반적인 상황에서의 입력을 처리한다.
void Player::UpdateInput(float dtSeconds) {
	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	const auto& Engine = (GameEngine*)(Scene->GetInstance());
	auto& Input = Engine->GetInputManager();

	if (Input.IsPressed(InputButton::A)) {
		_Position.x -= S.x * dtSeconds;
		SetFlipbook(_FlipbookMove[DIRECTION_LEFT]);
	}
	else if (Input.IsPressed(InputButton::D)) {
		_Position.x += S.x * dtSeconds;
		SetFlipbook(_FlipbookMove[DIRECTION_RIGHT]);
	}
	else if (Input.IsPressed(InputButton::W)) {
		_Position.y -= S.y * dtSeconds;
		SetFlipbook(_FlipbookMove[DIRECTION_UP]);
	}
	else if (Input.IsPressed(InputButton::S)) {
		_Position.y += S.y * dtSeconds;
		SetFlipbook(_FlipbookMove[DIRECTION_DOWN]);
	}
}

void Player::UpdateMoveScript(float dtSeconds) {
	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	const auto& Engine = (GameEngine*)(Scene->GetInstance());
	auto& Input = Engine->GetInputManager();
	
	상단과 하단에 충돌체가 있는 상태에서 점프를 반복할 때 밀어내는 처리로 인해 벽을 뚫는 버그가 발생한다.
	물론, 임시 코드이기 때문에 충돌 처리가 미흡한 부분이 있을 수 밖에 없다.

	러닝 게임도 좋아하기 때문에 언젠가 한 번쯤 고생해서 만들어 볼 필요가 있다고 생각된다.
	
	if (Input.IsPressed(InputButton::SpaceBar) && GetState() == OBJECTSTATE::Move) {
		SetState(OBJECTSTATE::Jump);
		S.y = -500.f;
	}
}

void Player::UpdateJumpScript(float dtSeconds) {
	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	const auto& Engine = (GameEngine*)(Scene->GetInstance());
	auto& Input = Engine->GetInputManager();

}
*/

/*
	PlayerState에서 ObjectState로 변경되었으며 기반 클래스에서 함수를 정의함
void Player::SetState(OBJECTSTATE State) {
	if (_State == State) { return; }
	_State = State;
	UpdateAnimation();
}
*/

void Player::UpdateAnimation() {
	switch (_State) {
	case OBJECTSTATE::IDLE:
		if (_KeyPressed) {
			SetFlipbook(_FlipbookMove[_Direction]);
		}
		else {
			SetFlipbook(_FlipbookIdle[_Direction]);
		}
		break;

	case OBJECTSTATE::MOVE:
		SetFlipbook(_FlipbookMove[_Direction]);
		break;

	case OBJECTSTATE::SKILL:
		if (_WeaponType == WEAPONTYPE::SWORD) {
			SetFlipbook(_FlipbookAttack[_Direction]);
		}
		else if (_WeaponType == WEAPONTYPE::BOW) {
			SetFlipbook(_FlipbookBow[_Direction]);
		}
		else if(_WeaponType == WEAPONTYPE::STAFF) {
			SetFlipbook(_FlipbookStaff[_Direction]);
		}
		break;
	}
}

void Player::UpdateIdle(float dtSeconds) {
	_KeyPressed = TRUE;

	Vector Delta[] = { Vector(0.f, -1.f), Vector(0.f, 1.f), Vector(-1.f, 0.f), Vector(1.f, 0.f) };
	
	const auto& Scene = (BaseScene*)GetScene();
	const auto& Engine = (GameEngine*)Scene->GetInstance();
	auto& Input = Engine->GetInputManager();

	/* 온라인 게임으로 변환할 때 코드 전체가 변한다. */
	if (Input.IsPressed(InputButton::W)) {
		SetDirection(DIRECTION_UP);

		Vector Next = _CellPosition + Delta[_Direction];
		if (MoveTo(Next)) {
			SetCellPosition(Next);
			SetState(OBJECTSTATE::MOVE);
		}
	}
	else if (Input.IsPressed(InputButton::S)) {
		SetDirection(DIRECTION_DOWN);

		Vector Next = _CellPosition + Delta[_Direction];
		if (MoveTo(Next)) {
			SetCellPosition(Next);
			SetState(OBJECTSTATE::MOVE);
		}
	}
	else if (Input.IsPressed(InputButton::A)) {
		SetDirection(DIRECTION_LEFT);

		Vector Next = _CellPosition + Delta[_Direction];
		if (MoveTo(Next)) {
			SetCellPosition(Next);
			SetState(OBJECTSTATE::MOVE);
		}
	}
	else if (Input.IsPressed(InputButton::D)) {
		SetDirection(DIRECTION_RIGHT);

		Vector Next = _CellPosition + Delta[_Direction];
		if (MoveTo(Next)) {
			SetCellPosition(Next);
			SetState(OBJECTSTATE::MOVE);
		}
	}
	else {
		_KeyPressed = FALSE;
		if (_State == OBJECTSTATE::IDLE) {
			UpdateAnimation();
		}
	}

	if (Input.IsPressed(InputButton::NUM_1)) {
		SetWeaponType(WEAPONTYPE::SWORD);
	}
	else if (Input.IsPressed(InputButton::NUM_2)) {
		SetWeaponType(WEAPONTYPE::BOW);
	}
	else if (Input.IsPressed(InputButton::NUM_3)) {
		SetWeaponType(WEAPONTYPE::STAFF);
	}

	if (Input.IsPressed(InputButton::SpaceBar)) {
		SetState(OBJECTSTATE::SKILL);
	}
}

void Player::UpdateMove(float dtSeconds) {
	Vector Dist = (_Destination - _Position);

	if (Dist.length() < 5.f) {
		SetState(OBJECTSTATE::IDLE);
		_Position = _Destination;
	}
	else {
		switch (_Direction) {
		case DIRECTION_UP:
			_Position.y -= 200.f * dtSeconds;
			break;
		case DIRECTION_DOWN:
			_Position.y += 200.f * dtSeconds;
			break;
		case DIRECTION_LEFT:
			_Position.x -= 200.f * dtSeconds;
			break;
		case DIRECTION_RIGHT:
			_Position.x += 200.f * dtSeconds;
			break;
		}
	}
}

void Player::UpdateSkill(float dtSeconds) {
	if (_Flipbook == NULL) { return; }
	
	if (IsAnimationEnded()) {
		// 피격 판정 등





		SetState(OBJECTSTATE::IDLE);
	}
}

/*
BOOL Player::MoveTo(Vector Position) {
	const auto& Scene = dynamic_cast<DevScene*>(GetScene());
	const auto& Engine = (GameEngine*)Scene->GetInstance();
	auto& Input = Engine->GetInputManager();

	if (Scene == NULL) { return FALSE; }
	return Scene->MoveTo(Position);
}

void Player::SetCellPosition(Vector Position, BOOL Teleport) {
	_CellPosition = Position;
	
	const auto& Scene = dynamic_cast<DevScene*>(GetScene());
	if (Scene == NULL) { return; }

	_Destination = Scene->Convert(_CellPosition);
	if (Teleport) { _Position = _Destination; }
}
*/


/*
	여기까지가 WinAPI의 클라이언트 실습이라고 볼 수 있다.

	캐릭터를 만들고 맵을 구현하고 기본적인 충돌 처리를 하는 것까지 마쳤다면 이제 서버로 넘어가야 한다.
	D2D 또는 서버 둘 중 무언가 하나를 시작해야 하는데 어느 직무를 지원할 것인가에 따라 우선순위가 바뀌며, 결과적으론 둘 다 공부해야 한다.

	D2D의 고급 기법을 배운다고 해도 거진 비슷한 수준이라고 한다.
	다만, 과정을 따라 포폴이 세네개 정도 추가되므로 시간을 쓴 만큼 도움이 된다는 의견도 많다.

	사실 Direction 2D는 WinAPI와 쉘을 공부하면서 COM과 클래스화 과정에서 이미 접해본 적 있다.
	
	전체적으로 구문에 변화가 생긴다는 것과 고급 기법을 배운다는 점에서 꽤 차이가 있으며,
	그래픽 관련 함수들도 더 방대해져 부릴 수 있는 기교가 늘어난다는 점도 상당히 매력적이다.
*/