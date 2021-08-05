#include "Texture.h"
#include "Renderer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

namespace Engine
{
	void Texture::Load(const std::string& file)
	{
		SDL_Renderer* renderer = Engine::Renderer::GetRenderer();
		SDL_Surface* surface = IMG_Load(file.c_str());
		if (surface == nullptr)
		{
			std::cout << "Error createing surface: " << SDL_GetError() << std::endl;
			return;
		}
		m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}

	Ref<Texture> Texture::Create()
	{
		return std::make_shared<Texture>();
	}

}