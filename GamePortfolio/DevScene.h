#pragma once

class DevScene : public BaseScene
{
public:
	DevScene();
	virtual ~DevScene();

public:
	virtual void Update(float);
	virtual void Render(HDC);
	virtual BOOL Initialize();
};

