#pragma once
#include "Component.h"

class CameraComponent : public Component
{
public:
	virtual BOOL Initialize();
	virtual void Update(float);
	virtual void Render(HDC);

public:
	CameraComponent();
	virtual ~CameraComponent();
};

