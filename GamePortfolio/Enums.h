#pragma once

enum class SceneType {
	None,
	DevScene,
	GameScene,
	EditScene,
	LobiScene,
	MenuScene,
	FortressScene,

	LastScene,
	LAST_SCENE_COUNT = LastScene
};

enum class PlayerType {
	CanonTank,
	MissileTank,

	PLAYER_TYPE_LAST_COUNT
};

enum class Direction {
	Left,
	Right,

	DIRECTION_TYPE_LAST_COUNT
};