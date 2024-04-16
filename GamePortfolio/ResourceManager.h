#pragma once

class ResourceBase;
class LineMesh;

class ResourceManager
{
public:
	~ResourceManager();

public:
	void Init();
	void Clear();

	const LineMesh* GetLineMesh(std::wstring Key);

private:
	std::unordered_map<std::wstring, LineMesh*> _LineMeshes;
};

