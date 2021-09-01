#include "Component.h"
#include "Math\Transform.h"
#include "Entity.h"
#include "Time.h"
#include "Application.h"
#include "Input\Input.h"
#include "Renderer\Renderer.h"
#include "Audio\Audio.h"
#include "SceneSerializer.h"

#include <iostream>

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
			sprite->m_Index = m_Frames[m_Frame];
		}
	}




	// player component
	void PlayerComponent::Update()
	{
		if (Transform().Position.y > Renderer::GetHeight())
		{
			Application::GetScene().Load("Scene.json");
		}

		if (m_DownSpeed != 0) 
		{
			Transform().Position.y += m_DownSpeed * Time::GetDeltaTime();
			return;
		}

		if (Input::GetButtonPressed(SDL_SCANCODE_SPACE))
		{
			if (Transform().Position.x == 180) 
				Transform().Position.x = 245;
			else if (Transform().Position.x == 245)
				Transform().Position.x = 180;

			int& index =  m_Entity->GetComponent<SpriteRendererComponent>()->m_Index;
			if (index == 0)
				index = 1;
			else if (index == 1)
				index = 0;

		}
	}

	void PlayerComponent::OnCollision(Entity* e)
	{
		if (e->HasComponent<SpikeComponent>())
		{
			std::cout << "GameOver!!!" << std::endl;
			std::cout << Transform().Position.y;
			m_DownSpeed = e->GetComponent<SpikeComponent>()->m_Speed;
		}
	}

	// Enemy Component
	void SpikeComponent::Update()
	{
		float dt = Time::GetDeltaTime();
		Transform().Position.y += m_Speed * dt;
	}
	

	// PickupComponent
	void PickupComponent::Update()
	{
		float dt = Time::GetDeltaTime();
		Transform().Position.y += m_Speed * dt;
	}

	void PickupComponent::OnCollision(Entity* e)
	{
		if (e->GetComponent<PlayerComponent>())
		{
			Application::GetScene().Destroy(m_Entity);
			Audio::PlayAudio("coin");
		}
	}

	// ManegerComponent
	void ManegerComponent::Update()
	{
		m_SpawnTimer += Time::GetDeltaTime();
		if (m_SpawnTimer >= m_SpawnRate)
		{
			Scene& scene = Application::GetScene();

			m_SpawnTimer = 0.0f;

			float r = Math::Random();
			if (r > 0.3333f) {

				Ref<Entity> entity;
				if (Math::Random() > 0.75f)
					entity = scene.Instantiate<Entity>(*scene.GetPrefab("coin").get());
				else
					entity = scene.Instantiate<Entity>(*scene.GetPrefab("spike").get());


				Math::Transform& t = entity->m_Transform;
				auto sprite = entity->GetComponent<SpriteRendererComponent>();

				t.Position.y = -10.0f;
				if (r > 0.6666f) {
					t.Position.x = 180;
					sprite->m_Index = 1;
				}
				else {
					t.Position.x = 245;
					sprite->m_Index = 0;
				}
			}
		}
	}

}