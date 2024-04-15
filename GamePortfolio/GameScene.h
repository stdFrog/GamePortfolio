#pragma once

class GameScene : public BaseScene
{
public:
	GameScene();
	virtual ~GameScene();
	
public:
	virtual void Update(float);
	virtual void Render(HDC);
	virtual BOOL Initialize();
};

