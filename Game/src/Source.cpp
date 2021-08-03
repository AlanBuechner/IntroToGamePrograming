#include <iostream>
#include <SDL.h>

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{ 
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl; 
		return 1; 
	}

	SDL_Window* window = SDL_CreateWindow("GAT150", 100, 100, 800, 600, SDL_WINDOW_SHOWN); 
	if (window == nullptr) 
	{ 
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl; 
		SDL_Quit(); 
		return 1; 
	}
	
	// wait for keyboard enter to exit
	std::getchar();

	SDL_Quit();
	return 0;
}