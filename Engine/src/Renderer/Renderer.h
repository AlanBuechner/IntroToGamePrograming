#pragma once
#include <SDL.h>
#include "..\Core.h"
#include "..\Math\Math.h"
#include "Texture.h"

namespace Engine
{
	class Renderer
	{
	public:
		static void Init();
		static void Destroy();

		static void BeginScene();
		static void EndScene();

		static void Draw(Ref<Texture> texutre, const Math::Transform& transform);
		static void Draw(Ref<Texture> texture, const Math::Vector2& pos, const Math::Vector2& scale, float angle);

		static SDL_Renderer* GetRenderer() { return s_Renderer; }

	private:
		static SDL_Renderer* s_Renderer;
	};
}