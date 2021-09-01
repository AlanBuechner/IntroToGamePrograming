#include "App.h"
#include <iostream>

void App::OnCreate()
{
	Engine::SceneSerializer::Deserealize("Scene.json", Engine::Application::GetScene());
}

void App::OnUpdate()
{

	if (Engine::Input::GetButtonDown(SDL_SCANCODE_ESCAPE))
		Quit();
}

void App::OnDraw()
{
}