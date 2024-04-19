#pragma once
#include "ResourceBase.h"

/* 이 구조체가 이미지 파일의 전체 형상을 가진다. */

class Texture :public ResourceBase
{
	int _TransParentColor = RGB(255, 0, 255);				// Magenta

	HDC _hMemDC = NULL;
	HBITMAP _hBitmap = NULL;

	Vector _ImageSize;

public:
	void SetSize(Vector ImageSize) { _ImageSize = ImageSize; }
	Vector GetSize() { return _ImageSize; }

public:
	HDC GetTextureDC() { return _hMemDC; }

	void SetTransParent(int Transparent) { _TransParentColor = Transparent; }
	int GetTransParent() { return _TransParentColor; }

public:
	Texture* LoadBmp(HWND hWnd, const std::wstring& Path);

public:
	Texture();
	virtual ~Texture();
};

