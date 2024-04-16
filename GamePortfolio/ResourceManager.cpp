#include "pch.h"
#include "ResourceManager.h"
#include "LineMesh.h"

ResourceManager::~ResourceManager() {
	Clear();
}

void ResourceManager::Init() {
	LineMesh* mesh = new LineMesh();
	mesh->Load(L"LineUnit.txt");

	_LineMeshes[L"LineUnit"] = mesh;
}

void ResourceManager::Clear() {
	for (auto mesh : _LineMeshes) {
		delete mesh.second;
		mesh.second = NULL;
	}
}

const LineMesh* ResourceManager::GetLineMesh(std::wstring Key) {
	auto Find = _LineMeshes.find(Key);
	if (Find == _LineMeshes.end()){
		return nullptr;
	}

	return Find->second;
}