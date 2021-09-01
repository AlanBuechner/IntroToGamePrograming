#pragma once
#include <string>
#include <SDL.h>

#include "..\Core.h"
#include "Math\Math.h"

namespace Engine
{
	class Texture
	{
	public:
		struct Atlis
		{
			int Cols = 1, Rows = 1;
		};

		void Load(const std::string& file);

		Math::Vector2 GetDimentions();
		SDL_Texture* GetTexture() { return m_Texture; }

		static Ref<Texture> Create();
		static Ref<Texture> Create(const std::string& file);

	public:
		Atlis m_Atlis;

	private:
		SDL_Texture* m_Texture = nullptr;
	};

}