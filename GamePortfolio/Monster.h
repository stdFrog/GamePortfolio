#pragma once

class Monster : public Creature
{
	using Super = Creature;

private:
	Flipbook* _FlipbookMove[4];

protected:
	virtual void UpdateIdle(float);
	virtual void UpdateMove(float);
	virtual void UpdateSkill(float);
	virtual void UpdateAnimation();

public:
	Monster();
	virtual ~Monster();

	virtual BOOL Initialize();			// Start
	virtual void Update(float);			// Update
	virtual void Render(HDC);			// Render
};

