#pragma once
#include "ResourceBase.h"

class LineMesh : public ResourceBase
{
protected:
	std::vector<std::pair<POINT, POINT>> _Lines;

public:
	std::vector<std::pair<POINT, POINT>>& GetLines() { return _Lines; }
	const std::vector<std::pair<POINT, POINT>>& GetLines() const { return _Lines; }

	void Save(std::wstring path);
	void Load(std::wstring path);

	void Render(HDC, Vector);
};

