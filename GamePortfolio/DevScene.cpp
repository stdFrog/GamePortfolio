#include "pch.h"
#include "Texture.h"
#include "Sprite.h"
#include "RectCollider.h"
#include "CircleCollider.h"
#include "UI.h"
#include "Button.h"
#include "ContentsPanel.h"

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
	Engine->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));

	Engine->CreateSprite(L"Stage01", Engine->GetTexture(L"Stage01"));
	Engine->CreateSprite(L"Tile_O", Engine->GetTexture(L"Tile"), 0, 0, 48,48);
	Engine->CreateSprite(L"Tile_X", Engine->GetTexture(L"Tile"), 48, 0, 48, 48);
	Engine->CreateSprite(L"Start_Off", Engine->GetTexture(L"Start"), 0, 0, 150, 150);
	Engine->CreateSprite(L"Start_On", Engine->GetTexture(L"Start"), 150, 0, 150, 150);
	Engine->CreateSprite(L"Edit_Off", Engine->GetTexture(L"Edit"), 0, 0, 150, 150);
	Engine->CreateSprite(L"Edit_On", Engine->GetTexture(L"Edit"), 150, 0, 150, 150);
	Engine->CreateSprite(L"Exit_Off", Engine->GetTexture(L"Exit"), 0, 0, 150, 150);
	Engine->CreateSprite(L"Exit_On", Engine->GetTexture(L"Exit"), 150, 0, 150, 150);

	/* IDLE */
	{
		Texture* T = Engine->GetTexture(L"PlayerUp");
		Flipbook* F = Engine->CreateFlipbook(L"FB_IdleUp");
		F->SetInfo({ T, L"FB_IdleUp", Vector(200, 200), 0, 9, 0, 0.5f});
	}

	{
		Texture* T = Engine->GetTexture(L"PlayerDown");
		Flipbook* F = Engine->CreateFlipbook(L"FB_IdleDown");
		F->SetInfo({ T, L"FB_IdleDown", Vector(200, 200), 0, 9, 0, 0.5f });
	}

	{
		Texture* T = Engine->GetTexture(L"PlayerLeft");
		Flipbook* F = Engine->CreateFlipbook(L"FB_IdleLeft");
		F->SetInfo({ T, L"FB_IdleLeft", Vector(200, 200), 0, 9, 0, 0.5f });
	}

	{
		Texture* T = Engine->GetTexture(L"PlayerRight");
		Flipbook* F = Engine->CreateFlipbook(L"FB_IdleRight");
		F->SetInfo({ T, L"FB_IdleRight", Vector(200, 200), 0, 9, 0, 0.5f });
	}

	/* MOVE */
	{
		Texture* T = Engine->GetTexture(L"PlayerUp");
		Flipbook* F = Engine->CreateFlipbook(L"FB_MoveUp");
		F->SetInfo({ T, L"FB_MoveUp", Vector(200, 200), 0, 9, 1, 0.5f });
	}

	{
		Texture* T = Engine->GetTexture(L"PlayerDown");
		Flipbook* F = Engine->CreateFlipbook(L"FB_MoveDown");
		F->SetInfo({ T, L"FB_MoveDown", Vector(200, 200), 0, 9, 1, 0.5f });
	}

	{
		Texture* T = Engine->GetTexture(L"PlayerLeft");
		Flipbook* F = Engine->CreateFlipbook(L"FB_MoveLeft");
		F->SetInfo({ T, L"FB_MoveLeft", Vector(200, 200), 0, 9, 1, 0.5f });
	}

	{
		Texture* T = Engine->GetTexture(L"PlayerRight");
		Flipbook* F = Engine->CreateFlipbook(L"FB_MoveRight");
		F->SetInfo({ T, L"FB_MoveRight", Vector(200, 200), 0, 9, 1, 0.5f });
	}

	/* Attack */
	{
		Texture* T = Engine->GetTexture(L"PlayerUp");
		Flipbook* F = Engine->CreateFlipbook(L"FB_AttackUp");
		F->SetInfo({ T, L"FB_AttackUp", Vector(200, 200), 0, 7, 3, 0.5f });
	}

	{
		Texture* T = Engine->GetTexture(L"PlayerDown");
		Flipbook* F = Engine->CreateFlipbook(L"FB_AttackDown");
		F->SetInfo({ T, L"FB_AttackDown", Vector(200, 200), 0, 7, 3, 0.5f });
	}

	{
		Texture* T = Engine->GetTexture(L"PlayerLeft");
		Flipbook* F = Engine->CreateFlipbook(L"FB_AttackLeft");
		F->SetInfo({ T, L"FB_AttackLeft", Vector(200, 200), 0, 7, 3, 0.5f });
	}

	{
		Texture* T = Engine->GetTexture(L"PlayerRight");
		Flipbook* F = Engine->CreateFlipbook(L"FB_AttackRight");
		F->SetInfo({ T, L"FB_AttackRight", Vector(200, 200), 0, 7, 3, 0.5f });
	}

	{
		Sprite* Temp = Engine->GetSprite(L"Stage01");
		
		SpriteActor* background = CreateActor<SpriteActor>();
		background->SetSprite(Temp);
		background->SetLayerType(LAYER_BACKGROUND);
		const Vector Size = Temp->GetSize();
		background->SetPosition(Vector(Size.x, Size.y));
		
		AppendActor(background);
	}

	{
		/*
			객체간의 그려질 순서를 일반 열거형 타입으로 구분지었다.

			간혹, 본인 같은 초보자가 그리기 순서를 헷갈리면 마땅히 그려져야 할 객체가
			화면에 그려지지 않을 수 있다.

			따라서, 아래와 같이 그려질 순서를 구분 지을 방법을 모색해 적용해두어야
			실수할 일이 적어진다.

			확실히 코드가 길어지긴 한다.
		*/
		Player* player = CreateActor<Player>();
		{
			// CircleCollider* collider = new CircleCollider;
			RectCollider* collider = new RectCollider;
			//collider->SetRadius(50.f);
			collider->SetSize(Vector(50.f, 50.f));
			AppendCollider(collider);
			collider->SetCollisionLayer(CLT_OBJECT);
			collider->SetCollisionFlagLayer((COLLISION_LAYER_TYPE)(CLT_WALL | CLT_OBJECT));
			player->AppendComponent(collider);
		}

		AppendActor(player);
	}

	{
		/*
			Player는 등장 요소이므로 컨텐츠에서 관리한다.
			
			즉, 엔진측에서 다룰 수 있는 지형/지물에서 충돌 처리를 하는 것이 일반적이다.
			때문에 실습과 달리 Collider에 관리 함수를 추가하기로 한다.
		*/
		/*
		Actor* CollisionTestRect = CreateActor<Actor>();
		{
			RectCollider* collider = new RectCollider();
			collider->SetSize(Vector(100.f, 100.f));
			collider->SetCollisionLayer(CLT_GROUND);
			CollisionTestRect->AppendComponent(collider);
			AppendCollider(collider);
			CollisionTestRect->SetPosition(Vector(400, 200));
		}

		AppendActor(CollisionTestRect);

		Actor* CollisionTestCircle = CreateActor<Actor>();
		{
			CircleCollider* collider = new CircleCollider();
			collider->SetRadius(50.f);
			collider->SetCollisionLayer(CLT_WALL);
			CollisionTestCircle->AppendComponent(collider);
			AppendCollider(collider);
			CollisionTestCircle->SetPosition(Vector(400, 400));
		}
		
		AppendActor(CollisionTestCircle);

		Actor* CollisionTest = CreateActor<Actor>();
		CollisionTest->SetLayerType(LAYER_OBJECT);
		{
			RectCollider* collider = new RectCollider();
			collider->SetSize(Vector(10000.f, 200.f));
			collider->SetCollisionLayer(CLT_GROUND);
			CollisionTest->AppendComponent(collider);
			AppendCollider(collider);
			CollisionTest->SetPosition(Vector(0,400));
		}

		AppendActor(CollisionTestCircle);
		*/
	}

	/*{
		UI를 확장하여 Panel이라는 관리 클래스를 만들었다.
		앞으로 생성될 UI는 Panel이 총 통합하여 관리한다.

		Button* Btn = new Button();
		Btn->SetSprite(Engine->GetSprite(L"Start_Off"), BS_DEFAULT);
		Btn->SetSprite(Engine->GetSprite(L"Start_On"), BS_CLICKED);
		Btn->SetPosition(Vector(200, 200));
		Btn->SetOwner(this);
		Btn->Initialize();
		_UserInterfaces.push_back(Btn);
	}*/
	/*{
		Panel의 구조는 일반적이지 않다.
		상속 및 포함 관계를 동시에 가지고 있는데 이렇게 설계할 필요가 없다.
		
		UI를 통합 관리하기 위한 클래스이므로 포함 관계를 유지하고, 상속은 제거한다.

		엔진측에선 Panel만을 관리 대상으로 하여 컨텐츠 측에서 Panel로부터 UI를 생성해
		관리할 수 있도록 구조를 개선한다.

		UI* GUI = CreateInterface<ContentsPanel>();
		_UserInterfaces.push_back(GUI);
	}*/
	/*{
		
			실습을 위한 임시 객체
			Panel* GUI = CreateUIPanel<ContentsPanel>();
			AppendUIPanel(GUI);

			GUI->Initialize();
	}*/

	/*
		리소스의 생성은 본래 게임이 시작됨과 동시에 이뤄지는게 일반적이라 한다.
		따라서, BaseScene의 추상화를 제거한 이후로부터 아래와 같은 리소스는
		BaseScene에서 관리하기로 한다.

	for (const std::vector<Actor*>& type : _Actors) {
		for (Actor* actor : type) {
			actor->Initialize();
		}
	}
	*/

	/*for (UI* ui : _UserInterfaces) {
		ui->Initialize();
	}*/
	
	{
		/*
			타일맵의 경우 충돌 처리 등의 용도로도 쓰이므로 빠른 검색이 가능해야 한다.
			씬에 임시 포인터를 두고 디버깅용으로 사용한다.
		*/
		TileMapActor* NewTileMapActor = CreateActor<TileMapActor>();
		AppendActor(NewTileMapActor);
		_TileMapActor = NewTileMapActor;
		{
			auto* M = Engine->CreateTileMap(L"TileMap_01");
			M->SetMapSize(Vector(63, 43));
			M->SetTileSize(48);

			Engine->LoadTileMap(L"TileMap_01", L"Tilemap\\Tilemap01_RESTORE.txt");
			_TileMapActor->SetTileMap(M);
			// _TileMapActor->SetVisible(TRUE);
			_TileMapActor->SetVisible(FALSE);
		}
	}

	/*
		현재는 실습을 간단히 하기 위해 소리와 관련된 기능을 검색하여 끌어다 쓴다.
		추후 FMOD라는 유명 라이브러리를 이용하여 음악이나, 효과음 등을 좀 더 편리하고
		쉽게 실행할 수 있으므로 자세한 분석은 필요없다고 한다.

		현재에 와서, Wave를 이용해 간단한 음악 재생기를 만든다거나 실무에서 Wave 파일을 직접 사용하는 등의 일은 극히 드물다.
		이유는 간단한데, Wave가 비압축 포맷이기 때문에 상대적으로 파일의 크기도 크고 사용 방법도 꽤나 연구해봐야 하기 때문이다.
		
		따라서, 게임을 만들 때에는 이미 제공되는 고수준의 라이브러리를 이용한다.

		사실, Wave 파일은 연구해볼만한 가치가 충분하다.

		Wave는 마이크로소프트와 IBM이 공식적으로 지원하는 포맷이며, 어느 운영체제에서건 실행될 수 있다는 장점이 있다.
		또, 현재 사용되는 오디오 파일 대부분이 Wave 파일로부터 파생되어 유사한 형식을 갖고 있다고 한다.

		때문에, 적어도 한 번은 연구해봐야 한다.
		
		오디오 파일의 포맷은 어떠한지, 소리를 만들어 파일로 저장하는 방법이 무엇인지,
		드라이버가 출력 장치에게 보내는 신호가 무엇인지 등의 세부적인 동작을 들여다 볼 수 있는 기회가 될 것이다. 

		LoadSound(L"BGM", L"Sound\\BGM.wav");
		{
			Sound* NewSound = GetSound(L"BGM");
			NewSound->Play(true);

		}
	*/

	Super::Initialize();

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

		이는 전체 구조를 보면 쉽게 이해되는데, 일단 등장 요소를 어떻게 관리하는지 살펴보자.

		현재 구조에선 객체를 표현하기 위해 하나의 큰 파일(비트맵)을 읽고
		사용할 영역을 직접 잘라내어(Sprite) 필요한 시기에 해당 이미지를 호출하여 객체를 표현한다.

		이때 사용되는 Sprite 클래스는 배경, 사물 등의 정적인 요소에서 활용된다.

		그런데, 게임은 정적인 요소만 있는 것이 아니다.
		동적인 요소, 예를 들어 캐릭터나 투사체, 몬스터 등을 표현하려면 어떻게 해야할까?

		말 그대로 애니메이션이 필요하기 때문에 이를 관리할 클래스가 추가되어야 한다.

		곧, Flipbook 클래스가 이 기능을 맡아 처리하는데 언리얼에서 애니메이션을 지칭할 때
		Flipbook 이라는 용어를 사용한다.

		이 클래스를 잘 살펴보면 왜 Super::Initialize 따위의 구문이 필요한지 알 수 있다.

		씬에 등장하는 요소는 각각이 유일한 객체로써 존재하지만, 리소스는 그렇지 않다.
		즉, 하나의 리소스에 여러 객체의 이미지가 담겨 있을 수 있다.
		
		이러한 리소스는 대개 일정한 크기로, 행과 열이 나누어져 있다.
		이는 곧, 동일한 크기의 이미지가 반복된다는 뜻이며 기반 클래스에서
		이에 필요한 처리를 끝내면 파생 클래스는 추가적인 동작을 할 필요가 없다는 뜻이다.
		
		기반 클래스에서 파생 클래스에 필요한 이미지의 초기화, 업데이트, 렌더링 과정을
		한꺼번에 관리할 수 있는 상태란 뜻이므로, 파생 클래스에선 기반 클래스의
		전체 로직을 한 번씩만 호출하면 된다.

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
				player->AppendComponent(SRD);
			}

			{
				PlayerMoveScript* Move = new PlayerMoveScript();
				player->AppendComponent(Move);
			}

			_GameObject = player;
		}

		_GameObject->Initialize();
	*/

	return TRUE;
}

void DevScene::Update(float dtSeconds) {
	Super::Update(dtSeconds);

	const auto& Engine = (GameEngine*)GetInstance();
	auto& Input = Engine->GetInputManager();

	/*if(Input.IsPressed(InputButton::Q)) {
		Engine->SaveTileMap(L"TileMap_01", L"Tilemap\\Tilemap01.txt");
	}
	if (Input.IsPressed(InputButton::E)) {
		Engine->LoadTileMap(L"TileMap_01", L"Tilemap\\Tilemap01.txt");
	}*/
}

void DevScene::Render(HDC hDC) {
	Super::Render(hDC);

	const auto& Engine = (GameEngine*)GetInstance();
	auto& Input = Engine->GetInputManager();

	POINT Mouse = Input.GetMousePosition();
	TCHAR str[256];
	wsprintf(str, TEXT("Mouse = (%d, %d)"), Mouse.x, Mouse.y);
	_TEXTOUT(hDC, 800, 0, str);
}


BOOL DevScene::MoveTo(Vector Position) {
	if (_TileMapActor == NULL) {
		return FALSE;
	}

	TileMap* M = _TileMapActor->GetTileMap();
	if (M == NULL) { return FALSE; }

	Tile* Target = M->GetTileAt(Position);
	if (Target == NULL) { return FALSE; }

	return Target->Number != TILETYPE::WALL;
}

Vector DevScene::Convert(Vector Position) {

}