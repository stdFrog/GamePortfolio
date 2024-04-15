#pragma once

class Player : public ObjectInterface
{
public:
	Player(ObjectType Type = ObjectType::Player);
	virtual ~Player();

	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};

