#pragma once

class LobiScene : public BaseScene
{
public:
	LobiScene();
	virtual ~LobiScene();
	
public:
	virtual void Update(float);
	virtual void Render(HDC);
	virtual BOOL Initialize();
};

