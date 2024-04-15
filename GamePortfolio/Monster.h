#pragma once

class Monster : public ObjectInterface
{
public:
	Monster(ObjectType Type = ObjectType::Monster);
	virtual ~Monster();

	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};

