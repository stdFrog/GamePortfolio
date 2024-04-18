#pragma once
#include "Fortress.h"

class FortressScene : public BaseScene
{
	Fortress UI;

	int _PlayerCount = 0;
	int _TurnObject = 1;
	float _SumTime = 0.f;
public:
	Fortress& GetUserInterface() { return UI; }
	const Fortress& GetUserInterface() const { return UI; }
	void ChangePlayerTurn();

public:
	FortressScene();
	virtual ~FortressScene();

	virtual void Update(float);
	virtual void Render(HDC);
	virtual BOOL Initialize();
};

