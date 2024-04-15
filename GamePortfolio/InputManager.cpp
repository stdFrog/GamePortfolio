#include "pch.h"

BOOL InputManager::Initialize(HWND hWnd) {
    _hWnd = hWnd;
	size_t MapSize = static_cast<size_t>(InputButton::INPUT_BUTTON_COUNT);

	_InputStateMap.resize(MapSize, InputState::None);
	if (_InputStateMap.empty()) { return FALSE; }

	return TRUE;
}

void InputManager::Update() {
    const int LayerCount = static_cast<int>(InputButton::INPUT_BUTTON_COUNT);
    
    BYTE Layers[LayerCount] = {};
    if (::GetKeyboardState(Layers) == FALSE) { return; };

    for (int index = 0; index < LayerCount; index++) {
        InputButton Btn = static_cast<InputButton>(index);
        InputState& State = _InputStateMap[index];

        if (Layers[index] & 0x80) {
            if (State == InputState::Pressed || State == InputState::Pressing) {
                State = InputState::Pressed;
            }
            else {
                State = InputState::Pressing;
            }
        }
        else {
            if (State == InputState::Pressed || State == InputState::Pressing) {
                State = InputState::Release;
            }
            else {
                State = InputState::None;
            }
        }
    }
 
    GetCursorPos(&_Mouse);
    ScreenToClient(_hWnd, &_Mouse);
}