#include "pch.h"
#include "Player.h"
#include "Flipbook.h"
#include "CameraComponent.h"

BOOL bOnGround;
Vector S(200.f,200.f), G(1000.f, 1000.f);

Player::Player() : FlipbookActor(ObjectType::Player) {

}

Player::~Player() {

}

BOOL Player::Initialize() {
	Super::Initialize();
	
	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	const auto& Engine = (GameEngine*)(Scene->GetInstance());

	_FlipbookUp = Engine->GetFlipbook(L"FB_MoveUp");
	_FlipbookDown = Engine->GetFlipbook(L"FB_MoveDown");
	_FlipbookLeft = Engine->GetFlipbook(L"FB_MoveLeft");
	_FlipbookRight = Engine->GetFlipbook(L"FB_MoveRight");

	CameraComponent* Camera = new CameraComponent();
	AppendComponent(Camera);

	SetFlipbook(_FlipbookRight);

	return TRUE;
}

void Player::Update(float dtSeconds) {
	Super::Update(dtSeconds);

	const auto& Scene = dynamic_cast<DevScene*>(_Scene);
	const auto& Engine = (GameEngine*)(Scene->GetInstance());
	auto& Input = Engine->GetInputManager();
	
	/* 
		단순히 벡터만을 사용할 때 다음과 같이 입력을 받아 이동 시킬 수 있다.

		이 경우엔 카메라의 위치도 직접 변경해야 하는데, 대부분 컴포넌트를 만들어 이어 붙이는 편이다. 
	*/

	if (!bOnGround) {
		S.y += G.y * dtSeconds;
		_Position.y += S.y * dtSeconds;
	}
	else {
		S = Vector(200.f, 200.f);
	}
	
	/*if (Input.IsPressed(InputButton::W)) {
		_Position.y -= S.y * dtSeconds;
		SetFlipbook(_FlipbookUp);
	}
	else if (Input.IsPressed(InputButton::S)) {
		_Position.y += S.y * dtSeconds;
		SetFlipbook(_FlipbookDown);
	} */
	if (Input.IsPressed(InputButton::A)) {
		_Position.x -= S.x * dtSeconds;
		SetFlipbook(_FlipbookLeft);
	}
	else if (Input.IsPressed(InputButton::D)) {
		_Position.x += S.x * dtSeconds;
		SetFlipbook(_FlipbookRight);
	}

	if (Input.IsPressed(InputButton::SpaceBar) && bOnGround) {
		bOnGround = FALSE;
		S.y = -500.f;
	}
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
	bOnGround = TRUE;
}

void Player::OnComponentEndOverlap(Collider* I, Collider* Target) {
	bOnGround = FALSE;
}