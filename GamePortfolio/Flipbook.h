#pragma once
#include "ResourceBase.h"

class Texture;
struct FlipbookInfo {
	Texture* texture = NULL;
	std::wstring name;
	Vector size;

	int start = 0, end = 0, line = 0;
	float duration = 1.f;
	BOOL loop = TRUE;
};

class Flipbook : public ResourceBase
{
	FlipbookInfo _Info;

public:
	void SetInfo(FlipbookInfo Info) { _Info = Info; }
	const FlipbookInfo& GetInfo() { return _Info; }

public:
	Flipbook();
	virtual ~Flipbook();
};

