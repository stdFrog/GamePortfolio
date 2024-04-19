#include "pch.h"
#include "Texture.h"

Texture::Texture() {
	// 생성시에 인수를 전달받아 이미지를 바로 로드하는게 더 좋다
}

Texture::~Texture() {
	if (_hBitmap) { DeleteObject(_hBitmap); }
	if (_hMemDC) { DeleteDC(_hMemDC);}
}

Texture* Texture::LoadBmp(HWND hWnd, const std::wstring& Path) {
	// DC 할당 해제 귀찮으면 클래스 스타일 수정할 것

	HDC hdc = GetDC(hWnd);			
	_hMemDC = CreateCompatibleDC(hdc);
	_hBitmap = (HBITMAP)LoadImage(nullptr, Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (_hBitmap == NULL) {
		WindowsUtility::Trace(TEXT("Image Load Failed"));
	}

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(_hMemDC, _hBitmap);
	DeleteObject(hOldBitmap);

	BITMAP bmp;
	GetObject(_hBitmap, sizeof(BITMAP), &bmp);

	_ImageSize.x = static_cast<float>(bmp.bmWidth);
	_ImageSize.y = static_cast<float>(bmp.bmHeight);

	
	ReleaseDC(hWnd, hdc);
	return this;
}