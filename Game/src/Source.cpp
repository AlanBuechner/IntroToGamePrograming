#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <Engine.h>

class App : public Engine::Applicaiton
{
protected:
	virtual void OnCreate()
	{
		m_Texture = Engine::Texture::Create();
		m_Texture->Load("sf2.png");

		m_Transform = { { 100,100 }, { 200,150 }, 45.0f };
	}

	virtual void OnUpdate()
	{
		if (Engine::Input::GetButtonDown(SDL_SCANCODE_W))
			m_Transform.Position += {0.0f, -0.5f};
		if (Engine::Input::GetButtonDown(SDL_SCANCODE_S))
			m_Transform.Position += {0.0f, 0.5f};
		if (Engine::Input::GetButtonDown(SDL_SCANCODE_A))
			m_Transform.Position += {-0.5f, 0.0f};
		if (Engine::Input::GetButtonDown(SDL_SCANCODE_D))
			m_Transform.Position += {0.5f, 0.0f};

		if (Engine::Input::GetButtonDown(SDL_SCANCODE_ESCAPE))
			Quit();

		Engine::Renderer::BeginScene();
		Engine::Renderer::Draw(m_Texture, m_Transform);
		Engine::Renderer::EndScene();
	}

	Engine::Ref<Engine::Texture> m_Texture;
	Math::Transform m_Transform;
};

int main(int argc, char** argv)
{
	
	App app;
	app.Init();
	app.Run();
	
	return 0;
}
