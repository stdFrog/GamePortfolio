#pragma once

class Arrow : public Projectile
{
	using Super = Projectile;

protected:
	virtual void UpdateIdle(float) {}
	virtual void UpdateMove(float) {}
	virtual void UpdateSkill(float) {}

	virtual void UpdateAnimation() {}

public:
	Arrow();
	virtual ~Arrow();

	virtual BOOL Initialize();			// Start
	virtual void Update(float);			// Update
	virtual void Render(HDC);			// Render
};

