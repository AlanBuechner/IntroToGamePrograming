#include "Entity.h"
#include "Renderer\Renderer.h"

namespace Engine
{
	Entity::Entity(const Math::Transform& t) :
		m_Transform(t)
	{}

	void Entity::Update(float dt)
	{
		for (auto& comp : m_Components)
		{
			comp->Update();
		}
	}

	void Entity::Draw()
	{
		SpriteRendererComponent* sprite = GetComponent<SpriteRendererComponent>();
		if(sprite)
			Renderer::Draw(sprite->m_Texture, m_Transform);
	}
	
}
