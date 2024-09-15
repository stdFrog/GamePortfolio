#pragma once

class Projectile : public GameObject
{
	using Super = GameObject;

protected:
	virtual void UpdateIdle(float) {}
	virtual void UpdateMove(float) {}
	virtual void UpdateSkill(float) {}

	virtual void UpdateAnimation() {}

public:
	Projectile();
	virtual ~Projectile();

	virtual BOOL Initialize();			// Start
	virtual void Update(float);			// Update
	virtual void Render(HDC);			// Render
};

