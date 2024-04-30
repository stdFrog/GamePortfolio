#include "pch.h"
#include "TileMap.h"

TileMap::TileMap() {

}

TileMap::~TileMap() {

}

void TileMap::LoadFile(const std::wstring& Path) {

}

void TileMap::SaveFile(const std::wstring& Path) {

}

Tile* TileMap::GetTileAt(Vector Position) {
	if (Position.x < 0 || Position.y >= _MapSize.x || Position.y < 0 || Position.y >= _MapSize.y) {
		return NULL;
	}

	return &_Tiles[Position.y][Position.x];
}

void TileMap::SetMapSize(Vector NewMapSize) {
	_MapSize = NewMapSize;

	_Tiles = std::vector<std::vector<Tile>>(NewMapSize.y, std::vector<Tile>(NewMapSize.x));

	for (int i = 0; i < NewMapSize.y; i++) {
		for (int j = 0; j < NewMapSize.x; j++) {
			_Tiles[i][j] = Tile{ 0 };
		}
	}
}

void TileMap::SetTileSize(LONG NewTileSize) {
	_TileSize = NewTileSize;

	// 다시 그려야할 때 필요한 처리를 한다.
}