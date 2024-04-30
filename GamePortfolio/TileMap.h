#pragma once
#include "ResourceBase.h"

struct Tile {
	int sz;
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

