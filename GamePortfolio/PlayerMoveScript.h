#pragma once

class PlayerMoveScript
{
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);
};