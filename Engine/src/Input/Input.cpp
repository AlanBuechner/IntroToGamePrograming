#include "Input.h"
#include <SDL.h>

std::vector<uint8_t> Engine::Input::m_KeyboardState;
std::vector<uint8_t> Engine::Input::m_PrevKeyboardState;
int Engine::Input::m_NumKeys;

namespace Engine
{
	void Input::Init()
	{
		const uint8_t* keyboardStateSDL = SDL_GetKeyboardState(&m_NumKeys);
		m_KeyboardState.resize(m_NumKeys);
		m_PrevKeyboardState.resize(m_NumKeys);

		std::copy(keyboardStateSDL, keyboardStateSDL + m_NumKeys, m_KeyboardState.begin());
	}

	void Input::Update()
	{
		m_PrevKeyboardState = m_KeyboardState;

		const uint8_t* keyboardStateSDL = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardStateSDL, keyboardStateSDL+m_NumKeys, m_KeyboardState.begin());
	}

	Input::KeyState Input::GetKeyState(int keycode)
	{
		return (KeyState)((uint8_t)(m_KeyboardState[keycode] != 0) | (uint8_t)(m_PrevKeyboardState[keycode] != 0) << 1);
	}

	bool Input::GetButtonDown(int keycode)
	{
		return m_KeyboardState[keycode] != 0;
	}

	bool Input::GetButtonUp(int keycode)
	{
		return m_KeyboardState[keycode] == 0;
	}

	bool Input::GetButtonPressed(int keycode)
	{
		return m_KeyboardState[keycode] != 0 && m_PrevKeyboardState[keycode] == 0;
	}

	bool Input::GetButtonRelesed(int keycode)
	{
		return m_KeyboardState[keycode] == 0 && m_PrevKeyboardState[keycode] != 0;
	}


}