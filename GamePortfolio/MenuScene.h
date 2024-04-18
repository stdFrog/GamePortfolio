#pragma once

class MenuScene : public BaseScene
{
public:
	MenuScene();
	virtual ~MenuScene();

	virtual void Update(float);
	virtual void Render(HDC);
	virtual BOOL Initialize();
};

