#include "pch.h"
#include "Texture.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "Player.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

DevScene::DevScene() {
	_hWnd = GetForegroundWindow();
	WindowsUtility::GetWindowSize(_hWnd, &iWidth, &iHeight);
}

DevScene::~DevScene() {

}

BOOL DevScene::Initialize() {
	// 엔진에서 공용으로 관리할 이미지 리소스를 관리하고
	// 씬에서는 해당 씬에서 사용할 것만 호출해서 사용하고 해제하고 반복
	const auto& Engine = (GameEngine*)_EngineInstance;

	Engine->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
	// Engine->LoadTexture(L"Sword", L"Sprite\\Item\\Sword.bmp");
	Engine->LoadTexture(L"Potion", L"Sprite\\UI\\Mp.bmp");
	Engine->LoadTexture(L"PlayerDown", L"Sprite\\Player\\PlayerDown.bmp", RGB(128, 128, 128));
	Engine->LoadTexture(L"PlayerUp", L"Sprite\\Player\\PlayerUp.bmp", RGB(128, 128, 128));
	Engine->LoadTexture(L"PlayerLeft", L"Sprite\\Player\\PlayerLeft.bmp", RGB(128, 128, 128));
	Engine->LoadTexture(L"PlayerRight", L"Sprite\\Player\\PlayerRight.bmp", RGB(128, 128, 128));
	Engine->LoadTexture(L"Start", L"Sprite\\UI\\Start.bmp");
	Engine->LoadTexture(L"Edit", L"Sprite\\UI\\Edit.bmp");
	Engine->LoadTexture(L"Exit", L"Sprite\\UI\\Exit.bmp");

	Engine->CreateSprite(L"Stage01", Engine->GetTexture(L"Stage01"));
	Engine->CreateSprite(L"Start_On", Engine->GetTexture(L"Start"), 0, 0, 150, 150);
	Engine->CreateSprite(L"Start_Off", Engine->GetTexture(L"Start"), 150, 0, 150, 150);
	Engine->CreateSprite(L"Edit_Off", Engine->GetTexture(L"Edit"), 0, 0, 150, 150);
	Engine->CreateSprite(L"Edit_On", Engine->GetTexture(L"Edit"), 150, 0, 150, 150);
	Engine->CreateSprite(L"Exit_Off", Engine->GetTexture(L"Exit"), 0, 0, 150, 150);
	Engine->CreateSprite(L"Exit_On", Engine->GetTexture(L"Exit"), 150, 0, 150, 150);

	{
		Sprite* Temp = Engine->GetSprite(L"Stage01");
		
		SpriteActor* background = new SpriteActor();
		background->SetSprite(Temp);
		const Vector Size = Temp->GetSize();
		background->SetPosition(Vector(Size.x / 2, Size.y / 2));
		
		_Actors.push_back(background);
	}
	
	{
		Sprite* Temp2 = Engine->GetSprite(L"Start_On");

		Player* player = new Player();
		player->SetSprite(Temp2);
		const Vector Size = Temp2->GetSize();
		player->SetPosition(Vector(Size.x / 2, Size.y / 2));

		_Actors.push_back(player);
	}

	for (Actor* actor : _Actors) {
		actor->Initialize();
	}

	/*
		상용 게임엔진에서 등장인물을 관리하는 방법에 대해 알아보자.
		언리얼과 유니티 엔진의 스타일을 따라 만들어보고 어떤 장단점이 있는지 살펴본다.

		먼저, 언리얼 스타일이다.
		언리얼은 네임 스페이스를 이용한 상속 설계를 택했다.

		주로 using Super = BaseClassName 따위의 구문을 이용하며
		다음과 같은 클래스로 씬에 추가해야될 요소를 관리한다.
		-> Actor, SpriteActor 등등

		여기서 SpriteActor를 굳이 나누는 이유는 어떠한 등장인물의 경우 Sprite가 그리기 동작이
		불필요할 수 있기 때문이며 엔진측에서 확장성을 고려해 세분화한 것으로 보인다.

		Actor가 씬을 구성하는 게임 내 오브젝트로서 현재 프로젝트와 비교했을 때
		ObjectInterface 클래스와 동일하다고 볼 수 있다.

		이외에도 특이한 점이 하나 있는데, 초기화, 업데이트, 렌더링 함수를 보면
		기반 클래스로부터 파생 클래스로의 흐름이 아닌 파생 클래스가 기반 클래스를 호출하는 형태를 갖고있다.

		한 예로, Player 클래스를 보자.
		
		이 클래스에서 초기화, 업데이트, 렌더링 로직을 맡은 함수들을 살펴보면 다음과 같은 구문을 볼 수 있다.
		Super::Initialize(), Super::Update(), Super::Render()

		네임 스페이스와 범위 연산자를 이용해 기반 클래스의 로직을 먼저 호출하고 있는데,
		이러한 설계 방식을 택한 이유가 무엇일까 고민해볼 필요가 있다.

		당장은 크게 두 가지 이유만 떠오르는데, 하나는 불필요한 정보의 노출을 최소화 한다는 점,
		또 하나는 로딩 속도를 높일 수 있다는 점 이 두 가지가 아닐까 싶다.

		자세한건 상용 엔진을 공부하게 되면 알아봐야겠다.

		{
			Sprite* Temp = Engine->GetSprite(L"Stage01");
			SpriteActor* background = new SpriteActor();
			background->SetSprite(Temp);
			const Vector Size = Temp->GetSize();
			background->SetPosition(Vector(Size.x / 2, Size.y / 2));
			_Background = background;

			Sprite* Temp2 = Engine->GetSprite(L"Start_On");

			Player* player = new Player();
			player->SetSprite(Temp2);
			const Vector Size = Temp2->GetSize();
			player->SetPosition(Vector(Size.x / 2, Size.y / 2));
			_Player = player;

			_Background->BeginPlay();
			_Player->BeginPlay();
		}
	*/
	/*
		두 번째는 유니티 스타일이다.
		
		유니티는 구조적 방식이 아닌 부품을 추가하는 Component 방식을 택했다.
		이 구조는 꽤 문제가 많은데 일단 SpriteRenderer의 Render함수를 보자.

		주석 처리해둔 BitBlt의 두 번째 인수를 보면,
		자신이 렌더링해야 하는 대상이 누구인지 알지 못하므로 _Position 변수를 읽을 수 없다.

		물론 간단히 해결할 수 있는데 Component 헤더를 살펴보자.
		클래스 하단에 자신이 누구의 소유인지 지정하는 변수를 가지고 있다.

		이렇게 설계하면 Private 멤버에 접근할 수 있는 public 함수를 이용해
		기본 상태 정보를 조정할 수 있을 것이다.

		그런데, 이렇게 할 필요가 있을까?

		상식적으로 씬에 등장하는 모든 대상은 자기 자신을 표현할 수 있어야 한다.
		즉, 자기 자신을 그려낼 수 있어야 한다는 것이다.

		유니티에서는 렌더링 기능까지 부품으로 떼어내어 컴포넌트로 관리하는 것으로 보이는데,
		이렇게까지 극한의 자유도를 추구하는 이유가 뭘까?

		설계의 용이성을 위해서라고 하지만, 나 같은 초보자에겐 혼란만 가중될 것 같다.

		어쨋거나, 유니티는 이러한 방식으로 각 부품을 설계한 후 다시 하나의 리소스로 관리하는데,
		이를 Flipbook이라 부른다.

		언리얼의 블루 프린트 클래스와 대칭적이라 보면 된다.
		{
			GameObject* player = new GameObject();
			player->SetPosition(Vector(500, 500));

			{
				Sprite* sprite = Engine->GetSprite(L"Start_On");
				SpriteRenderer* SRD = new SpriteRenderer();
				SRD->SetSprite(sprite);
				player->AddComponent(SRD);
			}

			{
				PlayerMoveScript* Move = new PlayerMoveScript();
				player->AddComponent(Move);
			}

			_GameObject = player;
		}

		_GameObject->Initialize();
	*/



	return TRUE;
}

void DevScene::Update(float dtSeconds) {
	for (Actor* actor : _Actors) {
		actor->Update(dtSeconds);
	}
}

void DevScene::Render(HDC hDC) {
	// const auto& Engine = (GameEngine*)_EngineInstance;
	// Texture* texture = Engine->GetTexture(L"Stage01");
	// Sprite* sprite = Engine->GetSprite(L"Start_On");

	// BOOL bRepaint = Engine->GetOnResizeState();
	// if (bRepaint) { WindowsUtility::GetWindowSize(_hWnd, &iWidth, &iHeight); }

	// BitBlt(hDC, 0, 0, iWidth, iHeight, sprite->GetSpriteDC(), sprite->GetPosition().x, sprite->GetPosition().y, SRCCOPY);
	
	for (Actor* actor : _Actors) {
		actor->Render(hDC);
	}
}