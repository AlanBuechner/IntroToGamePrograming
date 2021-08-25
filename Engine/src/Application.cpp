#include "Application.h"
#include "Renderer\Renderer.h"
#include "Input\Input.h"
#include "Audio\Audio.h"
#include "Time.h"

Engine::Application* Engine::Application::s_Instance = nullptr;

namespace Engine
{
	void Application::Init()
	{
		if (s_Instance != nullptr)
			return;

		s_Instance = this;

		Renderer::Init();
		Input::Init();
		Audio::Init();

		OnCreate();
	}

	void Application::Run()
	{
		SDL_Event e;
		while (!m_Quit)
		{
			SDL_PollEvent(&e);
			switch (e.type)
			{
			case SDL_QUIT:
				m_Quit = true;
				break;
			case SDL_WINDOWEVENT:
			{
				/*switch (e.window.event)
				{
					case SDL_WINDOWEVENT_RESIZED:
						width = e.window.data1;
						height = e.window.data2;
						break;
				}*/
				break;

			}
			}

			Input::Update();
			Time::UpdateDeltaTime();

			m_Scene.Update();
			OnUpdate();

			Renderer::BeginScene();
			m_Scene.Draw();
			OnDraw();
			Renderer::EndScene();
		}

		Renderer::Destroy();
		OnDestroy();
	}

}
