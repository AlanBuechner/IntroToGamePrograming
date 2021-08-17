#pragma once
#include <string>
#include <SDL.h>

#include "..\Core.h"

namespace Engine
{
	class Texture
	{
	public:
		void Load(const std::string& file);

		SDL_Texture* GetTexture() { return m_Texture; }

		static Ref<Texture> Create();
		static Ref<Texture> Create(const std::string& file);

	private:
		SDL_Texture* m_Texture = nullptr;
	};

}