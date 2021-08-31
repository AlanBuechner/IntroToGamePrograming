#include "Component.h"
#include "Math\Transform.h"
#include "Entity.h"
#include "Time.h"
#include "Application.h"
#include "Input\Input.h"
#include "Renderer\Renderer.h"
#include "Audio\Audio.h"

namespace Engine
{
	Math::Transform& Component::Transform()
	{
		return m_Entity->m_Transform;
	}

	void AnimationComponent::Update()
	{
		float dt = Time::GetDeltaTime();
		m_FrameTimer += dt;

		if (m_FrameTimer >= m_FrameTime)
		{
			m_FrameTimer = 0.0f;
			m_Frame++;
			if (m_Frame >= m_Frames.size())
				m_Frame = 0;

			auto sprite = m_Entity->GetComponent<SpriteRendererComponent>();
			sprite->m_Texture->m_Atlis.Index = m_Frames[m_Frame];
		}
	}




	// player component
	PlayerComponent* PlayerComponent::s_Instance;

	void PlayerComponent::OnCreate()
	{
		if (s_Instance != nullptr)
		{
			Application::GetScene().Destroy(m_Entity);
			return;
		}
		s_Instance = this;
	}

	void PlayerComponent::Update()
	{
		float dt = Time::GetDeltaTime();

		Math::Transform& t = Transform();
		Math::Vector2 dir = Math::Vector2::Rotate({ 1, 0 }, Math::DegToRad(t.Rotation)) * m_Speed * dt;
		if (Input::GetButtonDown(SDL_SCANCODE_W))
			t.Position += dir;
		if (Input::GetButtonDown(SDL_SCANCODE_S))
			t.Position -= dir;
		if (Input::GetButtonDown(SDL_SCANCODE_A))
			t.Rotation -= m_RotSpeed * dt;
		if (Input::GetButtonDown(SDL_SCANCODE_D))
			t.Rotation += m_RotSpeed * dt;

		m_FireTimer += dt;
		if (Input::GetButtonDown(SDL_SCANCODE_SPACE) && m_FireTimer >= m_FireRate)
		{
			m_FireTimer = 0;
			auto bullet = Application::GetScene().Instantiate<Entity>(t);
			bullet->AddComponent<BulletComponent>();
			bullet->AddComponent<CircleColliderComponent>();
		}
	}

	void PlayerComponent::OnCollision(Entity* e)
	{
		if (e->HasComponent<EnemyComponent>())
		{
			// game end
		}
	}



	// Bullet Component
	void BulletComponent::OnCreate()
	{
		m_Direction = Math::Vector2::Rotate({ 1,0 }, Math::DegToRad(Transform().Rotation));
		m_Entity->AddComponent<SpriteRendererComponent>(Texture::Create("sf2.PNG"));
	}

	void BulletComponent::Update()
	{
		Transform().Position += m_Direction * m_Speed * Time::GetDeltaTime();

		if (Transform().Position.x < 0 || Transform().Position.x > Renderer::GetWidth() ||
			Transform().Position.y < 0 || Transform().Position.y > Renderer::GetHeight())
		{
			Application::GetScene().Destroy(m_Entity);
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
		float dt = Time::GetDeltaTime();
		Math::Vector2 dirToPlayer = (m_Target->m_Transform.Position - t.Position).Normalized();
		float angle = Math::RadToDeg(atan2(dirToPlayer.y, dirToPlayer.x));
		t.Rotation = Math::alerp(t.Rotation, angle, dt);

		t.Position += dirToPlayer * m_Speed * dt;
	}

	void EnemyComponent::OnCollision(Entity* e)
	{
		if (e->HasComponent<PlayerComponent>() || e->HasComponent<BulletComponent>())
		{
			Application::GetScene().Destroy(m_Entity);
			//Application::GetScene().Destroy(e);

			Spawn();
		}
	}

	void EnemyComponent::Spawn()
	{
		int width = Renderer::GetWidth();
		int height = Renderer::GetHeight();
		Math::Vector2 pos = { Math::RandomIntRange(0, width), Math::RandomIntRange(0, height) };

		auto enemy = Application::GetScene().Instantiate<Entity>(Math::Transform{ pos, { 50,50 }, 0.0f });
		enemy->AddComponent<SpriteRendererComponent>(Texture::Create("sf2.PNG"));
		enemy->AddComponent<CircleColliderComponent>();
		enemy->AddComponent<EnemyComponent>();
	}
	
	// PickupComponent
	void PickupComponent::OnCollision(Entity* e)
	{
		if (e->GetComponent<PlayerComponent>())
		{
			Application::GetScene().Destroy(m_Entity);
			Audio::PlayAudio("coin");
		}
	}

}