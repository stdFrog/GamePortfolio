#pragma once

enum class InputState {
	None,
	Pressed,
	Pressing,
	Release,

	LastState,
	INPUT_STATE_COUNT = LastState
};

enum class InputButton
{
    LeftMouse = VK_LBUTTON,
    RightMouse = VK_RBUTTON,

    Up = VK_UP,
    Down = VK_DOWN,
    Left = VK_LEFT,
    Right = VK_RIGHT,
    SpaceBar = VK_SPACE,

    NUM_1 = '1',
    NUM_2 = '2',
    NUM_3 = '3',
    NUM_4 = '3',
    NUM_5 = '3',

    W = 'W',
    A = 'A',
    S = 'S',
    D = 'D',
    Q = 'Q',
    E = 'E',

    INPUT_BUTTON_COUNT = 256
};

class InputManager
{
private:
    HWND _hWnd;
    POINT _Mouse;
	std::vector<InputState> _InputStateMap;;

public:
	BOOL Initialize(HWND);
	void Update();

public:
	// Default Inline
	BOOL IsPressed(InputButton Btn) { return (GetKeyState(Btn) == InputState::Pressed); }
	BOOL IsPressing(InputButton Btn) { return (GetKeyState(Btn) == InputState::Pressing); }
	BOOL IsRelease(InputButton Btn) { return (GetKeyState(Btn) == InputState::Release); }

	InputState GetKeyState(InputButton Btn) { return _InputStateMap[static_cast<int>(Btn)]; }
    POINT GetMousePosition() { return _Mouse; }
};