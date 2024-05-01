#pragma once

class TileMap;

class TileMapActor : public Actor
{
	using Super = Actor;

	LONG Width, Height;

protected:
	TileMap* _TileMap = NULL;
	BOOL _bVisible = FALSE;

public:
	void SetTileMap(TileMap* NewTileMap) { _TileMap = NewTileMap; }
	void SetVisible(BOOL bVisible) { _bVisible = bVisible; }

	TileMap* GetTileMap() { return _TileMap; }

public:
	void TilePicking();

public:
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);

public:
	TileMapActor();
	virtual ~TileMapActor();
};