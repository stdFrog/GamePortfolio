#include "pch.h"
#include "TileMapActor.h"

TileMapActor::TileMapActor() {

}

TileMapActor::~TileMapActor() {

}

BOOL TileMapActor::Initialize() {
	Super::Initialize();

	return TRUE;
}

void TileMapActor::Update(float dtSeconds) {
	Super::Update(dtSeconds);

	TilePicking();
}

void TileMapActor::Render(HDC hDC) {
	Super::Render(hDC);

	if (_TileMap == NULL || _bVisible == FALSE) { return; }

	const Vector MapSize = _TileMap->GetMapSize();
	const LONG TileSize = _TileMap->GetTileSize();

	std::vector<std::vector<Tile>>& Tiles = _TileMap->GetTiles();

	const auto& Scene = (BaseScene*)GetScene();
	const auto& Engine = (GameEngine*)Scene->GetInstance();

	Sprite* O = Engine->GetSprite(L"Tile_O");
	Sprite* X = Engine->GetSprite(L"Tile_X");

	WindowsUtility::GetWindowSize(GetForegroundWindow(), &Width, &Height);
	Vector Camera = dynamic_cast<DevScene*>(Scene)->GetMainCamera().GetTransform().GetPosition();
	
	/*
		맵 전체를 그릴 필요는 없으므로 뷰포트에 포함되는 타일만 그린다.
		이를 컬링이라 부르는데 평면에서의 컬링은 뷰포트만 신경쓰면 된다.
	*/
	LONG L, T, R, B;
	L = static_cast<LONG>(Camera.x - (Width - 264) / 2);
	T = static_cast<LONG>(Camera.y - Height / 2);
	R = static_cast<LONG>(Camera.x + (Width + 264) / 2);
	B = static_cast<LONG>(Camera.y + Height / 2);

	POINT First, Last;
	First = { 
		static_cast<LONG>((L - _Position.x) / TILE_SIZEX),
		static_cast<LONG>((T - _Position.y) / TILE_SIZEY)
	};

	Last = {
		static_cast<LONG>((R - _Position.x) / TILE_SIZEX),
		static_cast<LONG>((B - _Position.y) / TILE_SIZEY)
	};

	for (int i = First.y; i <= Last.y; i++) {
		for (int j = First.x; j <= Last.x; j++) {
			if (j < 0 || j >= MapSize.x) { continue; }
			if (i < 0 || i >= MapSize.y) { continue; }

			switch (Tiles[i][j].Number) {
			case EMPTY:
				TransparentBlt(
					hDC,
					static_cast<int>(_Position.x + j * TILE_SIZEX - (Camera.x - (Width - 264) / 2)),
					static_cast<int>(_Position.y + i * TILE_SIZEY - (Camera.y - Height / 2)),
					TILE_SIZEX,
					TILE_SIZEY,
					O->GetSpriteDC(),
					static_cast<int>(O->GetPosition().x),
					static_cast<int>(O->GetPosition().y),
					TILE_SIZEX,
					TILE_SIZEY,
					O->GetTransparent());
				break;

			case WALL:
				TransparentBlt(
					hDC,
					static_cast<int>(_Position.x + j * TILE_SIZEX - (Camera.x - (Width - 264) / 2)),
					static_cast<int>(_Position.y + i * TILE_SIZEY - (Camera.y - Height / 2)),
					TILE_SIZEX,
					TILE_SIZEY,
					X->GetSpriteDC(),
					static_cast<int>(X->GetPosition().x),
					static_cast<int>(X->GetPosition().y),
					TILE_SIZEX,
					TILE_SIZEY,
					X->GetTransparent());
				break;
			}
		}
	}
}

/*
	타일의 정보를 변경하는 함수이다.

	타일은 충돌 처리에 주로 쓰이므로, 이에 대한 정보를 가지고 있다.
	이를 리소스 관리 툴로 관리하는데 현재 프로젝트는 그러한 툴을 제작하지 않았기 때문에
	임의로 해당 클래스에 필요한 함수를 추가했다.

	이러한 충돌 처리는 과거부터 많이 사용되어 왔으며 현재까지도 자주 사용된다.
	3D, 2D 구분없이 애용되는 기법이며 실시간 전투나 렌더링이 많은 프로그램에서 특히 유용하게 쓰인다.

	특히 연산이 많이 필요한 게임에서 충돌 처리에 소요되는 시간을 시간을 최소한으로 줄이기 위해 채택되는 방법이라고 한다.
*/
void TileMapActor::TilePicking() {
	const auto& Scene = (BaseScene*)GetScene();
	const auto& Engine = (GameEngine*)Scene->GetInstance();
	auto& Input = Engine->GetInputManager();
	
	auto& Camera = dynamic_cast<DevScene*>(Scene)->GetMainCamera();
	if(Input.IsPressed(InputButton::LeftMouse)){
		Vector CameraPosition = Camera.GetTransform().GetPosition();
		POINT Screen = { CameraPosition.x - (Width - 264) / 2, CameraPosition.y - Height / 2 };
		POINT Mouse = Input.GetMousePosition();
		POINT Logical = { Mouse.x + Screen.x, Mouse.y + Screen.y };
		POINT Pixel = { Logical.x / TILE_SIZEX, Logical.y / TILE_SIZEY };
		
		Tile* temp = _TileMap->GetTileAt(Vector(Pixel.x, Pixel.y));
		if (temp) {
			temp->Number = 1;
		}
	}

	if (Input.IsPressed(InputButton::RightMouse)) {
		Vector CameraPosition = Camera.GetTransform().GetPosition();
		POINT Screen = { CameraPosition.x - (Width - 264) / 2, CameraPosition.y - Height / 2 };
		POINT Mouse = Input.GetMousePosition();
		POINT Logical = { Mouse.x + Screen.x, Mouse.y + Screen.y };
		POINT Pixel = { Logical.x / TILE_SIZEX, Logical.y / TILE_SIZEY };

		Tile* temp = _TileMap->GetTileAt(Vector(Pixel.x, Pixel.y));
		if (temp) {
			temp->Number = 0;
		}
	}
}