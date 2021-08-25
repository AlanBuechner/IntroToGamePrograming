#include "Component.h"
#include "Math\Transform.h"
#include "Entity.h"
#include "Time.h"

namespace Engine
{
	Math::Transform& Engine::Component::Transform()
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
			sprite->m_Texture->m_Atlis.index = m_Frames[m_Frame];
		}
	}
}