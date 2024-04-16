#include "pch.h"
#include "LineMesh.h"
#include <fstream>

void LineMesh::Save(std::wstring path) {
	std::wofstream File;
	File.open(path);

	File << static_cast<int>(_Lines.size()) << std::endl;

	for (auto& Line : _Lines) {
		POINT From = Line.first;
		POINT To = Line.second;

		std::wstring String = std::format(L"({0},{1})->({2},{3})", From.x, From.y, To.x, To.y);
		File << String << std::endl;
	}

	File.close();
}

void LineMesh::Load(std::wstring path) {
	std::wifstream File;
	File.open(path);

	int Count;
	File >> Count;

	_Lines.clear();
	for (int i = 0; i < Count; i++) {
		POINT pt1, pt2;

		std::wstring String;
		File >> String;
		swscanf_s(String.c_str(), L"(%d,%d)->(%d,%d)", &pt1.x, &pt1.y, &pt2.x, &pt2.y);

		_Lines.push_back(std::make_pair(pt1, pt2));
	}

	File.close();
}

void LineMesh::Render(HDC hDC, Vector Position) {
	for (auto& Line : _Lines) {
		POINT pt1 = Line.first;
		POINT pt2 = Line.second;

		Vector From;
		From.x = Position.x + (float)pt1.x;
		From.y = Position.y + (float)pt1.y;

		Vector To;
		To.x = Position.x + (float)pt2.x;
		To.y = Position.y + (float)pt2.y;

		WindowsUtility::DrawLine(hDC, From, To);
	}
}