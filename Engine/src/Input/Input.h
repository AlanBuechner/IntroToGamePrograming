#pragma once
#include <vector>
#include "..\Core.h"

namespace Engine
{
	class Input
	{
	public:
		enum class KeyState : uint8_t
		{
			Pressed = 0b01,
			Relesed = 0b10,
			Down = 0b11,
			Up = 0b00
		};

		static void Init();
		static void Update();

		static KeyState GetKeyState(int keycode);
		static bool GetButtonDown(int keycode);
		static bool GetButtonUp(int keycode);
		static bool GetButtonPressed(int keycode);
		static bool GetButtonRelesed(int keycode);


	private:
		static std::vector<uint8_t> m_KeyboardState;
		static std::vector<uint8_t> m_PrevKeyboardState;
		static int m_NumKeys;
	};
}