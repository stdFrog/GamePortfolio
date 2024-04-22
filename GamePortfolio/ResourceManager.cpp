#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"

ResourceManager::~ResourceManager() {
	Clear();
}

void ResourceManager::Init(HWND hWnd, std::filesystem::path ResourcePath) {
	_hWnd = hWnd;
	_ResourcePath = ResourcePath;
}

void ResourceManager::Clear() {
	for (auto& Item : _Textures) {
		delete Item.second;
		Item.second = NULL;
	}

	_Textures.clear();
}

Texture* ResourceManager::LoadTexture(const std::wstring& Hash, const std::wstring& Path, int Transparent) {
	if (_Textures.find(Hash) != _Textures.end()) {
		return _Textures[Hash];
	}

	std::filesystem::path FullPath = _ResourcePath / Path;

	Texture* texture = new Texture();
	texture->LoadBmp(_hWnd, FullPath.c_str());
	texture->SetTransParent(Transparent);
	_Textures[Hash] = texture;

	return texture;
}

Sprite* ResourceManager::CreateSprite(const std::wstring& Hash, Texture* texture, int x, int y, int cx, int cy) {
	if (_Sprites.find(Hash) != _Sprites.end()) {
		return _Sprites[Hash];
	}

	if (cx == 0) {
		cx = static_cast<int>(texture->GetSize().x);
	}

	if (cy == 0) {
		cy = static_cast<int>(texture->GetSize().y);
	}

	Sprite* sprite = new Sprite(texture, x, y, cx, cy);
	_Sprites[Hash] = sprite;

	return sprite;
}