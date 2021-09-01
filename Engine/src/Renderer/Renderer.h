#pragma once
#include <SDL.h>
#include "Core.h"
#include "Math\Math.h"
#include "Texture.h"
#include "Font.h"
#include "Color.h"

namespace Engine
{
	class Renderer
	{
	public:
		static void Init();
		static void Destroy();

		static int GetWidth() { return s_Width; }
		static int GetHeight() { return s_Height; }

		static void BeginScene();
		static void EndScene();

		static void Draw(Ref<Texture> texutre, const Math::Transform& transform, int index = 0);
		static void Draw(Ref<Texture> texture, const Math::Vector2& pos, const Math::Vector2& scale, float angle, int index = 0);
		
		static void Draw(const std::string& text, const Font& font, const Color& color, const Math::Transform& transform);

		static SDL_Renderer* GetRenderer() { return s_Renderer; }

	private:
		static SDL_Renderer* s_Renderer;
		static int s_Width, s_Height;
	};
}