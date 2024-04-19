#pragma once

class ResourceBase;
class Texture;
class Sprite;

class ResourceManager
{
	HWND _hWnd;
	std::filesystem::path _ResourcePath;
	std::unordered_map<std::wstring, Texture*> _Textures;
	std::unordered_map<std::wstring, Sprite*> _Sprites;

public:
	const std::filesystem::path& GetResourcePath() { return _ResourcePath; }
	const std::filesystem::path& GetRelativePath() { return _ResourcePath.relative_path(); }
	const std::filesystem::path& GetCurrentFolder() { return std::filesystem::current_path(); }
	const std::filesystem::path& GetAbsolutePath() { return std::filesystem::absolute(_ResourcePath); }

public:
	// 확장용
	// Texture& CreateTexture(const std::wstring& Hash, const std::wstring& Path);
	// const Texture& CreateTexture(const std::wstring& Hash, const std::wstring& Path) const;
	// const Texture& GetTexture(const std::wstring& Hash) const { return *_Textures.at(Hash).get(); }

	Texture* GetTexture(const std::wstring& Hash) { return _Textures[Hash]; }
	Texture* LoadTexture(const std::wstring& Hash, const std::wstring& Path, int Transparent = RGB(255, 0, 255));

	Sprite* GetSprite(const std::wstring& Hash) { return _Sprites[Hash]; }
	Sprite* CreateSprite(const std::wstring& Hash, Texture* texture, int x = 0, int y = 0, int cx = 0, int cy = 0);

private:
	ResourceManager() {}

public:
	static ResourceManager* GetInstance() {
		static ResourceManager _Instance;
		return &_Instance;
	}

	~ResourceManager();

public:
	void Init(HWND hWnd, std::filesystem::path ResourcePath);
	void Clear();

};

