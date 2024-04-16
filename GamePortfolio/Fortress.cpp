#include "pch.h"
#include "Fortress.h"
#include "GameMath.h"

const int GWinSizeX = 1024;
const int GWinSizeY = 768;

const int GMinimapSizeX = 200;
const int GMinimapSizeY = 128;

void Fortress::Init()
{
	_windPercent = 50;
	_staminaPercent = 40;
	_remainTime = 7;
	_playerAngle = 0.f;
	_barrelAngle = 20.f;
}

void Fortress::Render(HDC hdc)
{
	RenderBackground(hdc);
	RenderWind(hdc);
	RenderPower(hdc);
	RenderStamina(hdc);
	RenderTime(hdc);
	RenderAngle(hdc);
	RenderWeaponChoice(hdc);
	RenderMiniMap(hdc);
}

void Fortress::RenderBackground(HDC hdc)
{
	/*const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(L"UI");
	if (mesh)
		mesh->Render(hdc, Pos{ 0, 0 });*/
}

void Fortress::RenderWind(HDC hdc)
{
	float minY = 560.0f / 600 * GWinSizeY;
	float maxY = 575.0f / 600 * GWinSizeY;
	float avgX = 100.0f / 800 * GWinSizeX;
	float sizeX = 49.0f / 800 * GWinSizeX;

	HBRUSH brush = ::CreateSolidBrush(RGB(50, 198, 74));
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

	if (_windPercent < 0)
	{
		Rectangle(hdc
			, static_cast<int>(avgX + sizeX * _windPercent / 100)
			, static_cast<int>(minY)
			, static_cast<int>(avgX)
			, static_cast<int>(maxY));
	}
	else
	{
		Rectangle(hdc
			, static_cast<int>(avgX)
			, static_cast<int>(minY)
			, static_cast<int>(avgX + sizeX * _windPercent / 100)
			, static_cast<int>(maxY));
	}

	::SelectObject(hdc, oldBrush);
	::DeleteObject(brush);
}

void Fortress::RenderPower(HDC hdc)
{
	{
		RECT rect = {};
		rect.left = static_cast<LONG>(265.0f / 800 * GWinSizeX);
		rect.top = static_cast<LONG>(505.0f / 600 * GWinSizeY);
		rect.right = static_cast<LONG>(680.0f / 800 * GWinSizeX);
		rect.bottom = static_cast<LONG>(535.0f / 600 * GWinSizeY);
		::Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	}

	{
		RECT rect = {};
		rect.left = static_cast<LONG>(270.0f / 800 * GWinSizeX);
		rect.top = static_cast<LONG>(510.0f / 600 * GWinSizeY);
		rect.right = static_cast<LONG>(270.0f / 800 * GWinSizeX + _powerPercent * 4);
		rect.bottom = static_cast<LONG>(530.0f / 600 * GWinSizeY);

		HBRUSH Brush, oBrush;
		Brush = ::CreateSolidBrush(RGB(255, 216, 216));
		oBrush = (HBRUSH)::SelectObject(hdc, Brush);

		::Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		::SelectObject(hdc, oBrush);
		::DeleteObject(Brush);
	}
}

void Fortress::RenderStamina(HDC hdc)
{
	{
		RECT rect = {};
		rect.left = static_cast<LONG>(265.0f / 800 * GWinSizeX);
		rect.top = static_cast<LONG>(538.0f / 600 * GWinSizeY);
		rect.right = static_cast<LONG>(680.0f / 800 * GWinSizeX);
		rect.bottom = static_cast<LONG>(568.0f / 600 * GWinSizeY);
		::Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	}
	{
		RECT rect = {};
		rect.left = static_cast<long>(270.0f / 800 * GWinSizeX);
		rect.top = static_cast<long>(543.0f / 600 * GWinSizeY);

		rect.right = static_cast<long>(270.0f / 800 * GWinSizeX + _staminaPercent * 4);

		rect.bottom = static_cast<long>(563.0f / 600 * GWinSizeY);

		HBRUSH brush = ::CreateSolidBrush(RGB(250, 236, 197));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

		::Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		::SelectObject(hdc, oldBrush);
		::DeleteObject(brush);
	}
}

void Fortress::RenderTime(HDC hdc)
{
	HFONT myFont = ::CreateFont(
		30
		, 0
		, 0	
		, 0	
		, 0	
		, 0	
		, 0	
		, 0	
		, DEFAULT_CHARSET
		, 0	
		, 0	
		, 0	
		, 0	
		, L"Times New Roman"
	);

	HFONT oldFont = (HFONT)::SelectObject(hdc, myFont);

	WCHAR message[100];
	::wsprintf(message, L"%02d", static_cast<int>(_remainTime));

	::TextOut(hdc, 728, 510, message, ::lstrlen(message));
	::SelectObject(hdc, oldFont);
	::DeleteObject(myFont);
}

void Fortress::RenderAngle(HDC hdc)
{
	::MoveToEx(hdc, 96, 520, nullptr);
	::Ellipse(hdc, 96 - 35, 520 - 35, 96 + 35, 520 + 35);

	::MoveToEx(hdc, 96, 520, nullptr);
	::LineTo(hdc
		, static_cast<int>(96 + 30 * ::cos(_playerAngle * GameMath::PI / 180.f))
		, static_cast<int>(520 - 30 * ::sin(_playerAngle * GameMath::PI / 180.f)));

	HPEN MyPen = ::CreatePen(PS_SOLID, 0, RGB(204, 61, 61));
	HPEN pOldPen = (HPEN)::SelectObject(hdc, MyPen);

	::MoveToEx(hdc, 96, 520, nullptr);

	::LineTo(hdc
		, static_cast<int>(96 + 30 * ::cos(_barrelAngle * GameMath::PI / 180.f))
		, static_cast<int>(520 + -30 * ::sin(_barrelAngle * GameMath::PI / 180.f)));

	::SelectObject(hdc, pOldPen);
	::DeleteObject(MyPen);
}

void Fortress::RenderWeaponChoice(HDC hdc)
{
	HBRUSH brush = ::CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

	if (_specialWeapon == false)
		::Rectangle(hdc, 20 - 5, 550 - 5, 20 + 5, 550 + 5);
	else
		::Rectangle(hdc, 170 - 5, 550 - 5, 170 + 5, 550 + 5);

	::SelectObject(hdc, oldBrush);
	::DeleteObject(brush);
}

void Fortress::RenderMiniMap(HDC hdc)
{
	float ratioX = static_cast<float>(GMinimapSizeX) / static_cast<float>(1280);
	float ratioY = static_cast<float>(GMinimapSizeY) / static_cast<float>(720);

	RECT rect = { GWinSizeX - GMinimapSizeX - 10, 10, GWinSizeX - 10, 10 + GMinimapSizeY };

	::Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}