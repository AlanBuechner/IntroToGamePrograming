#include "Application.h"
#include "Renderer\Renderer.h"
#include "Input\Input.h"

namespace Engine
{
	void Applicaiton::Init()
	{
		Renderer::Init();
		Input::Init();

		OnCreate();
	}

	void Applicaiton::Run()
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
			OnUpdate();
		}

		Renderer::Destroy();
		OnDestroy();
	}

}
