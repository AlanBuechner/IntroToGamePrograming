#include "App.h"
#include <iostream>

void App::OnCreate()
{
	/*auto player = GetScene().Instantiate<Engine::Entity>(Math::Transform{ { 800,100 },{ 50,50 }, 0.0f });
	auto sprite = player->AddComponent<Engine::SpriteRendererComponent>(Engine::Texture::Create("sf2.PNG"));
	sprite->m_Texture->m_Atlis = {2,2,0};
	player->AddComponent<Engine::AnimationComponent>(1.0f, std::vector<int>{0,1,2,3});
	player->AddComponent<Engine::CircleColliderComponent>();
	player->AddComponent<PlayerComponent>();

	EnemyComponent::Spawn();
	EnemyComponent::Spawn();
	EnemyComponent::Spawn();*/

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