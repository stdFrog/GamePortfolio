#include "pch.h"
#include "UI.h"

UI::UI() {

}

UI::~UI() {

}

BOOL UI::Initialize() {
	return TRUE;
}

void UI::Update(float dtSeconds) {

}

void UI::Render(HDC hDC) {

}

RECT UI::GetRect() {
	RECT rt = {
		static_cast<LONG>(_Position.x - _Size.x / 2),
		static_cast<LONG>(_Position.y - _Size.y / 2),
		static_cast<LONG>(_Position.x + _Size.x / 2),
		static_cast<LONG>(_Position.y + _Size.y / 2)
	};

	return rt;
}

BOOL UI::IsMouseInRect() {
	RECT rt = GetRect();

	const auto& Engine = (GameEngine*)_Owner->GetInstance();
	auto& Input = Engine->GetInputManager();

	POINT Mouse = Input.GetMousePosition();
	return PtInRect(&rt, Mouse);
}