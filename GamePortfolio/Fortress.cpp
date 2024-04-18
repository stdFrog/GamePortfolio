#include "pch.h"
#include "Fortress.h"

BOOL Fortress::Initialize(void* Instance)
{
	_windPercent = 50;
	_staminaPercent = 40;
	_remainTime = 10;
	_playerAngle = 0.f;
	_barrelAngle = 20.f;

	_Instance = Instance;
	_hWnd = GetForegroundWindow();
	WindowsUtility::GetWindowSize(_hWnd, &Width, &Height);

	return TRUE;
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
	LineMesh Line = ((GameEngine*)_Instance)->GetLineMesh(L"UI");
	Line.Render(hdc, Vector{ 0, 0 });
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
	
	RECT prt = {};
	prt.left = static_cast<LONG>((265.0f / 800) * GWinSizeX);
	prt.top = static_cast<LONG>((505.0f / 600) * GWinSizeY);
	prt.right = static_cast<LONG>((680.0f / 800) * GWinSizeX);
	prt.bottom = static_cast<LONG>((535.0f / 600) * GWinSizeY);
	::Rectangle(hdc, prt.left, prt.top, prt.right, prt.bottom);
	

	
	RECT prt2 = {};
	prt2.left = static_cast<LONG>((270.0f / 800) * GWinSizeX);
	prt2.top = static_cast<LONG>((510.0f / 600) * GWinSizeY);
	prt2.right = static_cast<LONG>((270.0f / 800) * GWinSizeX + _powerPercent * 4);
	prt2.bottom = static_cast<LONG>((530.0f / 600) * GWinSizeY);

	HBRUSH Brush, oBrush;
	Brush = ::CreateSolidBrush(RGB(255, 216, 216));
	oBrush = (HBRUSH)::SelectObject(hdc, Brush);

	::Rectangle(hdc, prt2.left, prt2.top, prt2.right, prt2.bottom);

	::SelectObject(hdc, oBrush);
	::DeleteObject(Brush);
	
}

void Fortress::RenderStamina(HDC hdc)
{
	
	RECT srt = {};
	srt.left = static_cast<LONG>(265.0f / 800 * GWinSizeX);
	srt.top = static_cast<LONG>(538.0f / 600 * GWinSizeY);
	srt.right = static_cast<LONG>(680.0f / 800 * GWinSizeX);
	srt.bottom = static_cast<LONG>(568.0f / 600 * GWinSizeY);
	::Rectangle(hdc, srt.left, srt.top, srt.right, srt.bottom);
	
	RECT srt2 = {};
	srt2.left = static_cast<long>(270.0f / 800 * GWinSizeX);
	srt2.top = static_cast<long>(543.0f / 600 * GWinSizeY);

	srt2.right = static_cast<long>(270.0f / 800 * GWinSizeX + _staminaPercent * 4);

	srt2.bottom = static_cast<long>(563.0f / 600 * GWinSizeY);

	HBRUSH brush = ::CreateSolidBrush(RGB(250, 236, 197));
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

	::Rectangle(hdc, srt2.left, srt2.top, srt2.right, srt2.bottom);

	::SelectObject(hdc, oldBrush);
	::DeleteObject(brush);
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

	{
		HPEN MyPen = ::CreatePen(PS_SOLID, 0, RGB(0, 0, 255));
		HPEN pOldPen = (HPEN)::SelectObject(hdc, MyPen);

		::MoveToEx(hdc, 96, 520, nullptr);
		::LineTo(hdc,
			static_cast<int>(96 + 30 * ::cos(_playerAngle * GameMath::PI / 180.f)),
			static_cast<int>(520 - 30 * ::sin(_playerAngle * GameMath::PI / 180.f)));

		::SelectObject(hdc, pOldPen);
		::DeleteObject(MyPen);
	}

	{
		HPEN MyPen = ::CreatePen(PS_SOLID, 0, RGB(204, 61, 61));
		HPEN pOldPen = (HPEN)::SelectObject(hdc, MyPen);

		::MoveToEx(hdc, 96, 520, nullptr);
		::LineTo(hdc,
			static_cast<int>(96 + 30 * ::cos(_barrelAngle * GameMath::PI / 180.f)),
			static_cast<int>(520 + -30 * ::sin(_barrelAngle * GameMath::PI / 180.f)));

		::SelectObject(hdc, pOldPen);
		::DeleteObject(MyPen);
	}
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