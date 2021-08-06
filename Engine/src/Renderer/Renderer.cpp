#include "Renderer.h"
#include "Texture.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

SDL_Renderer* Engine::Renderer::s_Renderer;

namespace Engine
{
	void Renderer::Init()
	{

		int width = 800;
		int height = 600;

		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return;
		}

		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

		SDL_Window* window = SDL_CreateWindow("GAT150", 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window == nullptr)
		{
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			IMG_Quit();
			return;
		}

		s_Renderer = SDL_CreateRenderer(window, -1, 0);

	}

	void Renderer::Destroy()
	{
		SDL_DestroyRenderer(s_Renderer);
		IMG_Quit();
		SDL_Quit();
	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
		SDL_RenderPresent(s_Renderer);
		SDL_RenderClear(s_Renderer);
	}

	void Renderer::Draw(Ref<Texture> texture, const Math::Transform& transform)
	{
		Draw(texture, transform.Position, transform.Scale, transform.Rotation);
	}

	void Renderer::Draw(Ref<Texture> texture, const Math::Vector2& pos, const Math::Vector2& scale, float angle)
	{
		SDL_Rect dest{(int)pos.x, (int)pos.y, (int)scale.x, (int)scale.y};
		SDL_RenderCopyEx(s_Renderer, texture->GetTexture(), nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
	}

}
