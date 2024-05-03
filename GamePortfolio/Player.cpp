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

Player::Player() : FlipbookActor(ObjectType::Player) {

}

Player::~Player() {

}

BOOL Player::Initialize() {
	Super::Initialize();
	
	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
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

	CameraComponent* Camera = new CameraComponent();
	AppendComponent(Camera);

	SetFlipbook(_FlipbookIdle[DIRECTION_DOWN]);

	return TRUE;
}

void Player::Update(float dtSeconds) {
	Super::Update(dtSeconds);

	switch (_State) {
	case PlayerState::Idle:
		UpdateIdle(dtSeconds);
		break;

	case PlayerState::Move:
		UpdateMove(dtSeconds);
		break;

	case PlayerState::Skill:
		UpdateSkill(dtSeconds);
		break;
	}

	/*UpdateGravity(dtSeconds);
	UpdateInput(dtSeconds);

	switch (GetState()) {
	case PlayerState::Move:
		UpdateMoveScript(dtSeconds);
		break;

	case PlayerState::Jump:
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

void Player::OnComponentBeginOverlap(Collider* I, Collider* Target) {
	/*SetState(PlayerState::Move);
	S = Vector(200.f, 200.f);*/
}

void Player::OnComponentEndOverlap(Collider* I, Collider* Target) {
	// SetState(PlayerState::Jump);
}

void Player::UpdateGravity(float dtSeconds) {
	if (GetState() == PlayerState::Move) { return; }
	S.y += G.y * dtSeconds;
	_Position.y += S.y * dtSeconds;
}

/* 특수 상황이 아닌 일반적인 상황에서의 입력을 처리한다. */
void Player::UpdateInput(float dtSeconds) {
	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	const auto& Engine = (GameEngine*)(Scene->GetInstance());
	auto& Input = Engine->GetInputManager();

	if (Input.IsPressed(InputButton::A)) {
		_Position.x -= S.x * dtSeconds;
		SetFlipbook(_FlipbookLeft);
	}
	else if (Input.IsPressed(InputButton::D)) {
		_Position.x += S.x * dtSeconds;
		SetFlipbook(_FlipbookRight);
	}
}

void Player::UpdateMoveScript(float dtSeconds) {
	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	const auto& Engine = (GameEngine*)(Scene->GetInstance());
	auto& Input = Engine->GetInputManager();
	/*
		상단과 하단에 충돌체가 있는 상태에서 점프를 반복할 때 밀어내는 처리로 인해 벽을 뚫는 버그가 발생한다.
		물론, 임시 코드이기 때문에 충돌 처리가 미흡한 부분이 있을 수 밖에 없다.

		러닝 게임도 좋아하기 때문에 언젠가 한 번쯤 고생해서 만들어 볼 필요가 있다고 생각된다.
	*/
	if (Input.IsPressed(InputButton::SpaceBar) && GetState() == PlayerState::Move) {
		SetState(PlayerState::Jump);
		S.y = -500.f;
	}
}

void Player::UpdateJumpScript(float dtSeconds) {
	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	const auto& Engine = (GameEngine*)(Scene->GetInstance());
	auto& Input = Engine->GetInputManager();

}

void Player::SetState(PlayerState State) {
	_State = State;
	UpdateAnimation();
}

void Player::SetDirection(DIRECTION Direction) {
	_Direction = Direction;
	UpdateAnimation();
}

void Player::UpdateAnimation() {
	switch (_State) {
	case PlayerState::Idle:
		if (_KeyPressed) {
			SetFlipbook(_FlipbookMove[_Direction]);
		}
		else {
			SetFlipbook(_FlipbookIdle[_Direction]);
		}
		break;

	case PlayerState::Move:
		SetFlipbook(_FlipbookMove[_Direction]);
		break;

	case PlayerState::Skill:
		SetFlipbook(_FlipbookAttack[_Direction]);
		break;
	}
}

void Player::UpdateIdle(float dtSeconds) {
	_KeyPressed = TRUE;

	Vector Delta[] = { Vector(0.f, -1.f), Vector(0.f, 1.f), Vector(-1.f, 0.f), Vector(1.f, 0.f) };
	
	const auto& Scene = (BaseScene*)GetScene();
	const auto& Engine = (GameEngine*)Scene->GetInstance();
	auto& Input = Engine->GetInputManager();

	if (Input.IsPressed(InputButton::W)) {
		SetDirection(DIRECTION_UP);

		Vector Next = _CellPosition + Delta[_Direction];
		if (MoveTo(Next)) {
			SetCellPosition(Next);
			SetState(PlayerState::Move);
		}
	}
	else if (Input.IsPressed(InputButton::S)) {
		SetDirection(DIRECTION_DOWN);

		Vector Next = _CellPosition + Delta[_Direction];
		if (MoveTo(Next)) {
			SetCellPosition(Next);
			SetState(PlayerState::Move);
		}
	}
	else if (Input.IsPressed(InputButton::A)) {
		SetDirection(DIRECTION_LEFT);

		Vector Next = _CellPosition + Delta[_Direction];
		if (MoveTo(Next)) {
			SetCellPosition(Next);
			SetState(PlayerState::Move);
		}
	}
	else if (Input.IsPressed(InputButton::D)) {
		SetDirection(DIRECTION_RIGHT);

		Vector Next = _CellPosition + Delta[_Direction];
		if (MoveTo(Next)) {
			SetCellPosition(Next);
			SetState(PlayerState::Move);
		}
	}
	else {
		_KeyPressed = FALSE;
		if (_State == PlayerState::Idle) {
			UpdateAnimation();
		}
	}
}

void Player::UpdateMove(float dtSeconds) {
	Vector Dist = (_Destination - _Position);
	if (Dist.length() < 10.f) {
		SetState(PlayerState::Idle);
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

}

BOOL Player::MoveTo(Vector Position) {
	const auto& Scene = dynamic_cast<DevScene*>(GetScene());
	const auto& Engine = (GameEngine*)Scene->GetInstance();
	auto& Input = Engine->GetInputManager();

	if (Scene == NULL) { return FALSE; }
	return Scene->MoveTo(Position);
}

Vector Player::Convert(Vector Position) {

}