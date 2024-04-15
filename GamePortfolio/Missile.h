#pragma once

class Missile : public ObjectInterface
{
public:
	Missile(ObjectType Type = ObjectType::Projectile);
	virtual ~Missile();

	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};

