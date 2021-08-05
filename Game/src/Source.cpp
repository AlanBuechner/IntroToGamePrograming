#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <Engine.h>

class App : public Engine::Aplicaiton
{
protected:
	virtual void OnCreate() 
	{
		m_Texture = Engine::Texture::Create();
		m_Texture->Load("sf2.png");
	}

	virtual void OnUpdate() 
	{
		Engine::Renderer::BeginScene();
		Engine::Renderer::Draw(m_Texture, { 0,0 }, { 1,1 }, 0.0f);
		Engine::Renderer::EndScene();
	}

	Engine::Ref<Engine::Texture> m_Texture;
};

int main(int argc, char** argv)
{
	
	App app;
	app.Init();
	app.Run();

	Engine::Texture texture;
	texture.Load("sf2.png");
	
	return 0;
}
