#include "pch.h"
#include "EditScene.h"
#include <fstream>

EditScene::EditScene() {

}

EditScene::~EditScene() {

}

BOOL EditScene::Initialize() {
	_bOrigin = TRUE;
	_bPaint = FALSE;

	return TRUE;
}

void EditScene::Update(float dtSeconds) {
	const auto& Engine = (GameEngine*)_EngineInstance;
	auto& Input = ((GameEngine*)Engine)->GetInputManager();

	if (Input.IsPressed(InputButton::LeftMouse)) {
		POINT MousePosition = Input.GetMousePosition();

		if (0/*_CommonObject.Type == EditTool::ET_PAINT*/) {
			GetClientRect(GetActiveWindow(), &_crt);
			_StartPoint = MousePosition;
			_bPaint = TRUE;
		}
		else {
			if (_bOrigin) {
				_LastPosition = MousePosition;
				_bOrigin = FALSE;
			}
			else {
				if (_Lines.empty()) {
					_Lines.push_back(std::make_pair(_LastPosition, MousePosition));
				}
				else {
					if (_LastPosition.x != MousePosition.x && _LastPosition.y != MousePosition.y) {
						_Lines.push_back(std::make_pair(_LastPosition, MousePosition));
					}
				}
				_LastPosition = MousePosition;
			}
		}
	}

	if (Input.IsPressed(InputButton::RightMouse)) {
		_bOrigin = TRUE;
	}

	if (Input.IsPressed(InputButton::S)) {
		std::wofstream File;
		File.open(L"LineUnit.txt");

		File << static_cast<int>(_Lines.size()) << std::endl;

		for (auto& Line : _Lines) {
			POINT From = Line.first;
			POINT To = Line.second;

			std::wstring String = std::format(L"({0},{1})->({2},{3})", From.x, From.y, To.x, To.y);
			File << String << std::endl;
		}

		File.close();
	}

	if (Input.IsPressed(InputButton::W)) {
		std::wifstream File;
		File.open(L"LineUnit.txt");

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

		_bOrigin = TRUE;
		File.close();
	}

	if (Input.IsPressed(InputButton::SpaceBar)) {
		_Lines.clear();
		InvalidateRect(GetActiveWindow(), NULL, TRUE);
	}
}

void EditScene::Render(HDC hDC) {
	for (auto& Line : _Lines) {
		Vector From(static_cast<float>(Line.first.x), static_cast<float>(Line.first.y));
		Vector To(static_cast<float>(Line.second.x), static_cast<float>(Line.second.y));
		WindowsUtility::DrawLine(hDC, From, To);
	}

	/*if (_bPaint) {
		_bPaint = FALSE;
		COLORREF StartColor = GetPixel(hDC, _StartPoint.x, _StartPoint.y);
		Fill(hDC, _StartPoint, StartColor, _CommonObject.PlaneColor);
	}*/
}

void EditScene::Fill(HDC hdc, POINT StartPoint, COLORREF StartColor, COLORREF FillColor) {
	// 시작 칸, 목표 색, 대체 색
	// 주변 픽셀 탐색 후 해당 색으로 색칠
	Fill(hdc, StartPoint.x, StartPoint.y, StartColor, FillColor);
}

void EditScene::Fill(HDC hdc, int x, int y, COLORREF StartColor, COLORREF FillColor) {
	// 에디트 씬 제대로 만들거면 최적화 필요
	// 여기선 실습에 목적을 두고 더 이상 진행하지 않음
	if (x < 0 || x > _crt.right || y < 0 || y > _crt.bottom) { return; }

	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };

	COLORREF Target = GetPixel(hdc, x, y);
	if (Target == FillColor) { return; }
	if (Target != StartColor) { return; }

	SetPixel(hdc, x, y, FillColor);
	for (int i = 0; i < 4; i++) {
		Fill(hdc, x + dx[i], y + dy[i], StartColor, FillColor);
	}
}
