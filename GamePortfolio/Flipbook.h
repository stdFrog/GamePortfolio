#pragma once
#include "ResourceBase.h"

class Texture;
struct FlipbookInfo {
	Texture* texture = NULL;
	std::wstring name;
	Vector size;

	int start = 0;
	int end = 0;
	int line = 0;

	float duration = 1.f;
	BOOL loop = TRUE;
};

class Flipbook : public ResourceBase
{
public:
	FlipbookInfo _Info;

public:
	void SetInfo(FlipbookInfo Info) { _Info = Info; }
	FlipbookInfo& GetInfo() { return _Info; }
	const FlipbookInfo& GetInfo() const { return _Info; }

public:
	Flipbook();
	virtual ~Flipbook();
};

