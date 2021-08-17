#pragma once
#include "Core.h"
#include <string>
#include <SDL_ttf.h>

namespace Engine
{
	class Renderer;
}

namespace Engine
{
	class Font
	{
	public:
		bool Load(const std::string& name, int ptSize);

	private:
		TTF_Font* m_Font{ nullptr };

		friend Renderer;
	};
}
