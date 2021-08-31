#include "Entity.h"
#include "Renderer\Renderer.h"

namespace Engine
{
	Entity::Entity(const Math::Transform& t) :
		m_Tag("Empty"), m_Transform(t)
	{}

	Entity::Entity(const std::string & tag, const Math::Transform & t) :
		m_Tag(tag), m_Transform(t)
	{}

	void Entity::Update()
	{
		for (auto& comp : m_Components)
		{
			comp->Update();
		}
	}

	void Entity::Draw()
	{
		auto sprite = GetComponent<SpriteRendererComponent>();
		if(sprite)
			Renderer::Draw(sprite->m_Texture, m_Transform);

		auto text = GetComponent<TextRendererComponent>();
		if (text)
			Renderer::Draw(text->m_Text, text->m_Font, text->m_Color, m_Transform);
	}

	void Entity::OnCollision(Entity* e)
	{
		for (auto& comp : m_Components)
		{
			comp->OnCollision(e);
		}
	}
	
}
