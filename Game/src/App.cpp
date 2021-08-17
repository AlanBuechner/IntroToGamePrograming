#include "App.h"

void App::OnCreate()
{
	GetScene().Instantiate<Player>();

	m_Font.Load("Roboto-Black.ttf", 16);
}

void App::OnUpdate()
{

	if (Engine::Input::GetButtonDown(SDL_SCANCODE_ESCAPE))
		Quit();
}

void App::OnDraw()
{
}

// -------- Player
void Player::OnCreate()
{
	m_Transform = { { 100,100 },{ 200,150 }, 0.0f };
	m_Texture = Engine::Texture::Create();
	m_Texture->Load("sf2.png");
}

void Player::Update(float dt)
{
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_W))
		m_Transform.Position += {0.0f, -0.5f};
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_S))
		m_Transform.Position += {0.0f, 0.5f};
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_A))
		m_Transform.Position += {-0.5f, 0.0f};
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_D))
		m_Transform.Position += {0.5f, 0.0f};
}
