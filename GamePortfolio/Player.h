#pragma once

enum class PlayerType {
	CanonTank,
	MissileTank,

	PLAYER_TYPE_LAST_COUNT
};

class Player : public ObjectInterface
{
private:
	PlayerType _PlayerType = PlayerType::CanonTank;
	LONG _PlayerID = 0;
	BOOL _PlayerTurn = FALSE;
	float _FireAngle = 0.f;

public:
	void SetPlayerType(PlayerType Type) { _PlayerType = Type; }
	void SetPlayerID(LONG ID) { _PlayerID = ID; }
	void SetPlayerTurn(BOOL Turn) { _PlayerTurn = Turn; }

	LONG GetPlayerID() const { return _PlayerID; }
	BOOL GetPlayerTurn() const { return _PlayerTurn; }
	PlayerType GetPlayerType() const { return _PlayerType; }

public:
	std::wstring GetMeshName();

public:
	void UpdateFireAngle();

public:
	Player(ObjectType Type = ObjectType::Player);
	virtual ~Player();

	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};

