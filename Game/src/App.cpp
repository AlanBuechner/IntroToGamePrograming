#include "App.h"

void App::OnCreate()
{
	auto entity = GetScene().Instantiate<Engine::Entity>(Math::Transform{ { 100,100 },{ 200,150 }, 0.0f });
	entity->AddComponent<Engine::SpriteRendererComponent>(Engine::Texture::Create("sf2.PNG"));
	entity->AddComponent<PlayerComponent>();
	
}

void App::OnUpdate()
{
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_ESCAPE))
		Quit();
}

void App::OnDraw()
{
}

// player component
void PlayerComponent::Update()
{
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_W))
		m_Entity->m_Transform.Position += {0.0f, -0.5f};
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_S))
		m_Entity->m_Transform.Position += {0.0f, 0.5f};
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_A))
		m_Entity->m_Transform.Position += {-0.5f, 0.0f};
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_D))
		m_Entity->m_Transform.Position += {0.5f, 0.0f};
}
