#pragma once
#include "ResourceBase.h"

typedef enum {EMPTY, WALL} TILETYPE;
typedef enum {TILE_WIDTH = 63, TILE_HEIGHT = 43, TILE_SIZEX = 48, TILE_SIZEY = 48} TILESIZE;

struct Tile {
	int Number;
};

class TileMap : public ResourceBase
{
	LONG _TileSize;
	Vector _MapSize;
	std::vector<std::vector<Tile>> _Tiles;

public:
	virtual void LoadFile(const std::wstring& Path);
	virtual void SaveFile(const std::wstring& Path);

public:
	Vector GetMapSize() { return _MapSize; }
	LONG GetTileSize() { return _TileSize; }
	Tile* GetTileAt(Vector);
	std::vector<std::vector<Tile>>& GetTiles() { return _Tiles; }

	void SetMapSize(Vector NewMapSize);
	void SetTileSize(LONG NewTileSize);

public:
	TileMap();
	virtual ~TileMap();
};

