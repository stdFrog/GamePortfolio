#include "pch.h"
#include "LineMesh.h"
#include <fstream>

void LineMesh::Save(std::wstring path) {
	std::wofstream File;
	File.open(path);

	POINT Min = { INT32_MAX, INT32_MAX }, Max = {INT32_MIN, INT32_MIN};

	for (auto& Line : _Lines) {
		POINT From = Line.first;
		POINT To = Line.second;

		Min.x = min(min(Min.x, From.x), To.x);
		Min.y = min(min(Min.y, From.y), To.y);
		Max.x = max(max(Max.x, From.x), To.x);
		Max.y = max(max(Max.y, From.y), To.y);
	}

	POINT Mid = { (Max.x + Min.x) / 2, (Max.y + Min.y) / 2 };

	File << static_cast<int>(_Lines.size()) << std::endl;

	for (auto& Line : _Lines) {
		POINT From = Line.first;
		POINT To = Line.second;

		From.x -= Mid.x;
		From.y -= Mid.y;

		To.x -= Mid.x;
		To.y -= Mid.y;

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

	POINT Min = { INT32_MAX, INT32_MAX }, Max = { INT32_MIN, INT32_MIN };

	for (auto& Line : _Lines) {
		POINT From = Line.first;
		POINT To = Line.second;

		Min.x = min(min(Min.x, From.x), To.x);
		Min.y = min(min(Min.y, From.y), To.y);
		Max.x = max(max(Max.x, From.x), To.x);
		Max.y = max(max(Max.y, From.y), To.y);
	}

	_iWidth = Max.x - Min.x;
	_iHeight = Max.y - Min.y;
}

void LineMesh::Render(HDC hDC, Vector Position, float ratioX, float ratioY) {
	for (auto& Line : _Lines) {
		POINT p1 = Line.first, pt2 = Line.second;

		Vector From(Line.first.x * ratioX + Position.x, Line.first.y * ratioY + Position.y);
		Vector To(Line.second.x * ratioX + Position.x, Line.second.y * ratioY + Position.y);

		WindowsUtility::DrawLine(hDC, From, To);
	}
}