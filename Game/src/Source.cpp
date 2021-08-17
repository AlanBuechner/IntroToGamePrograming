#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "App.h"

int main(int argc, char** argv)
{
	
	App app;
	app.Init();
	app.Run();
	
	return 0;
}
