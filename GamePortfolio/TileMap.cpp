#include "pch.h"
#include "TileMap.h"

typedef enum { MAP } DATA;

typedef enum { VECTOR } STRUCT;

typedef struct tag_FileHeader {
	DATA DataType;
	STRUCT StructType;
	char szHeader[32];
	int Version;
}FileHeader;

TileMap::TileMap() {

}

TileMap::~TileMap() {

}

void TileMap::LoadFile(const std::wstring& Path) {
	FILE* file = NULL;
	_wfopen_s(&file, Path.c_str(), L"rb");
	assert(file != NULL);

	fread(&_MapSize.x, sizeof(_MapSize.x), 1, file);
	fread(&_MapSize.y, sizeof(_MapSize.y), 1, file);

	SetMapSize(_MapSize);

	for (int i = 0; i < _MapSize.y; i++) {
		for (int j = 0; j < _MapSize.x; j++) {
			int ReadValue = -1;
			fread(&ReadValue, sizeof(ReadValue), 1, file);
			_Tiles[i][j].Number = ReadValue;
		}
	}

	fclose(file);

	/*
		C++

		std::wofstream File;
		File.open(Path);
		File >> _MapSize.x >> _MapSize.y;

		SetMapSize(_MapSize);

		for (int i = 0; i < _MapSize.y; i++) {
			for (int j = 0; j < _MapSize.x; j++) {
				File >> _MapSize[i][j].Number;
			}
		}
		File.close();
	*/
}

void TileMap::SaveFile(const std::wstring& Path) {

	FILE* file = NULL;
	_wfopen_s(&file, Path.c_str(), L"wb");
	assert(file != NULL);

	fwrite(&_MapSize.x, sizeof(_MapSize.x), 1, file);
	fwrite(&_MapSize.y, sizeof(_MapSize.y), 1, file);

	for (int i = 0; i < _MapSize.y; i++) {
		for (int j = 0; j < _MapSize.x; j++) {
			int WriteValue = _Tiles[i][j].Number;
			fwrite(&WriteValue, sizeof(WriteValue), 1, file);
		}
	}

	fclose(file);

	/*
		C++

		std::wofstream File;
		File.open(Path);
		File << _MapSize.x << _MapSize.y;

		for (int i = 0; i < _MapSize.y; i++) {
			for (int j = 0; j < _MapSize.x; j++) {
				File << _MapSize[i][j].Number;
			}
		}
		File.close();
	*/
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