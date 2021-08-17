#include "Font.h"
#include <iostream>
#include <SDL_ttf.h>

namespace Engine
{
	bool Font::Load(const std::string& name, int ptSize)
	{
		m_Font = TTF_OpenFont(name.c_str(), ptSize);
		if (m_Font == nullptr)
		{
			std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl; 
			return false; 
		}
		return true;
	}

}
