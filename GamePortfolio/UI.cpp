#include "pch.h"
#include "UI.h"

UI::UI(){

}

UI::~UI() {

}

BOOL UI::Initialize() {
	return TRUE;
}

void UI::Update(float dtSeconds) {
	// 이미지 애니메이션 등
}

void UI::Render(HDC hDC) {
	// 이미지 출력
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

	const auto& Scene = (BaseScene*)(((Panel*)_Owner)->GetOwner());
	const auto& Engine = (GameEngine*)Scene->GetInstance();
	auto& Input = Engine->GetInputManager();

	POINT Mouse = Input.GetMousePosition();
	return PtInRect(&rt, Mouse);
}