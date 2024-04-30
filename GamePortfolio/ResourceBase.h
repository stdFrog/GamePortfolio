#pragma once
class ResourceBase
{
public:
	ResourceBase();
	virtual ~ResourceBase();

	virtual void LoadFile(const std::wstring& Path);
	virtual void SaveFile(const std::wstring& Path);
};

