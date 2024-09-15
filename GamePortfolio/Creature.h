#pragma once

class Creature : public GameObject
{
	using Super = GameObject;

protected:
	Status _Status;

	void SetStatus(Status NewStatus) { _Status = NewStatus; }
	const Status GetStatus() const { return _Status; }

protected:
	virtual void UpdateIdle(float) {}
	virtual void UpdateMove(float) {}
	virtual void UpdateSkill(float) {}

	virtual void UpdateAnimation() {}

public:
	Creature(ObjectType Type = ObjectType::None);
	virtual ~Creature();

	virtual BOOL Initialize();			// Start
	virtual void Update(float);			// Update
	virtual void Render(HDC);			// Render
};

