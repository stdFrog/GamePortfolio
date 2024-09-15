#pragma once

class HitEffect : public GameObject
{
	using Super = GameObject;

protected:
	virtual void UpdateIdle(float) {}
	virtual void UpdateMove(float) {}
	virtual void UpdateSkill(float) {}

	virtual void UpdateAnimation() {}

public:
	HitEffect();
	virtual ~HitEffect();

	virtual BOOL Initialize();			// Start
	virtual void Update(float);			// Update
	virtual void Render(HDC);			// Render
};

