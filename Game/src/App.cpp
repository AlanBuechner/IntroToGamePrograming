#include "App.h"
#include <iostream>

void App::OnCreate()
{
	auto player = GetScene().Instantiate<Engine::Entity>(Math::Transform{ { 800,100 },{ 50,50 }, 0.0f });
	auto sprite = player->AddComponent<Engine::SpriteRendererComponent>(Engine::Texture::Create("sf2.PNG"));
	sprite->m_Texture->m_Atlis = {2,2,0};
	player->AddComponent<Engine::AnimationComponent>(1.0f, std::vector<int>{0,1,2,3});
	player->AddComponent<Engine::CircleColliderComponent>();
	player->AddComponent<PlayerComponent>();

	EnemyComponent::Spawn();
	EnemyComponent::Spawn();
	EnemyComponent::Spawn();
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
PlayerComponent* PlayerComponent::s_Instance;

void PlayerComponent::OnCreate()
{
	if (s_Instance != nullptr)
	{
		Engine::Application::GetScene().Destroy(m_Entity);
		return;
	}
	s_Instance = this;
}

void PlayerComponent::Update()
{
	float dt = Engine::Time::GetDeltaTime();

	Math::Transform& t = Transform();
	Math::Vector2 dir = Math::Vector2::Rotate({ 1, 0 }, Math::DegToRad(t.Rotation)) * m_Speed * dt;
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_W))
		t.Position += dir;
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_S))
		t.Position -= dir;
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_A))
		t.Rotation -= m_RotSpeed * dt;
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_D))
		t.Rotation += m_RotSpeed * dt;

	m_FireTimer += dt;
	if (Engine::Input::GetButtonDown(SDL_SCANCODE_SPACE) && m_FireTimer >= m_FireRate)
	{
		m_FireTimer = 0;
		auto bullet = Engine::Application::GetScene().Instantiate<Engine::Entity>(t);
		bullet->AddComponent<BulletComponent>();
		bullet->AddComponent<Engine::CircleColliderComponent>();
	}
}

void PlayerComponent::OnCollision(Engine::Entity* e)
{
	if (e->HasComponent<EnemyComponent>())
	{
		// game end
	}
}


// Bullet Component
void BulletComponent::OnCreate()
{
	m_Direction = Math::Vector2::Rotate({1,0}, Math::DegToRad(Transform().Rotation));
	m_Entity->AddComponent<Engine::SpriteRendererComponent>(Engine::Texture::Create("sf2.PNG"));
}

void BulletComponent::Update()
{
	Transform().Position += m_Direction * m_Speed * Engine::Time::GetDeltaTime();

	if (Transform().Position.x < 0 || Transform().Position.x > Engine::Renderer::GetWidth() ||
		Transform().Position.y < 0 || Transform().Position.y > Engine::Renderer::GetHeight())
	{
		Engine::Application::GetScene().Destroy(m_Entity);
	}
}

// Enemy Component
void EnemyComponent::OnCreate()
{
	m_Target = PlayerComponent::Get()->m_Entity;
}

void EnemyComponent::Update()
{
	Math::Transform& t = Transform();
	float dt = Engine::Time::GetDeltaTime();
	Math::Vector2 dirToPlayer = (m_Target->m_Transform.Position - t.Position).Normalized();
	float angle = Math::RadToDeg(atan2(dirToPlayer.y, dirToPlayer.x));
	t.Rotation = Math::alerp(t.Rotation, angle, dt);

	t.Position += dirToPlayer * m_Speed * dt;
}

void EnemyComponent::OnCollision(Engine::Entity* e)
{
	if (e->HasComponent<PlayerComponent>() || e->HasComponent<BulletComponent>())
	{
		Engine::Application::GetScene().Destroy(m_Entity);
		//Engine::Application::GetScene().Destroy(e);

		Spawn();
	}
}

void EnemyComponent::Spawn()
{
	int width = Engine::Renderer::GetWidth();
	int height = Engine::Renderer::GetHeight();
	Math::Vector2 pos = { Math::RandomIntRange(0, width), Math::RandomIntRange(0, height) };

	auto enemy = Engine::Application::GetScene().Instantiate<Engine::Entity>(Math::Transform{ pos, { 50,50 }, 0.0f });
	enemy->AddComponent<Engine::SpriteRendererComponent>(Engine::Texture::Create("sf2.PNG"));
	enemy->AddComponent<Engine::CircleColliderComponent>();
	enemy->AddComponent<EnemyComponent>();
}
