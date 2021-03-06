#include "Renderer.h"
#include "Texture.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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

		TTF_Init();

		s_Renderer = SDL_CreateRenderer(window, -1, 0);

	}

	void Renderer::Destroy()
	{
		SDL_DestroyRenderer(s_Renderer);
		TTF_Quit();
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
		SDL_Rect dest{(int)pos.x - scale.x/2.0f, (int)pos.y - scale.y/2.0f, (int)scale.x, (int)scale.y};
		SDL_RenderCopyEx(s_Renderer, texture->GetTexture(), nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
	}

	void Renderer::Draw(const std::string& text, const Font& font, const Color& color, const Math::Transform& transform)
	{
		uint8_t r, g, b;
		r = (uint8_t)(color.r * 255.0f);
		g = (uint8_t)(color.g * 255.0f);
		b = (uint8_t)(color.b * 255.0f);

		SDL_Surface* surface = TTF_RenderText_Solid(font.m_Font, text.c_str(), SDL_Color({ r, g, b, 255 }));
		if (surface == nullptr)
			std::cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << std::endl; 
	
		SDL_Texture* texture = SDL_CreateTextureFromSurface(s_Renderer, surface);
		SDL_FreeSurface(surface);

		Math::Vector2 pos = transform.Position;
		Math::Vector2 scale = transform.Scale;

		SDL_Rect dest{ (int)pos.x - scale.x / 2.0f, (int)pos.y - scale.y / 2.0f, (int)scale.x, (int)scale.y };
		SDL_RenderCopyEx(s_Renderer, texture, nullptr, &dest, transform.Rotation, nullptr, SDL_FLIP_NONE);

	}

}
