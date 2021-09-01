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

	Entity::Entity(const Entity & other)
	{
		m_Scene = other.m_Scene;
		m_Tag = other.m_Tag;
		m_Transform = other.m_Transform;

		m_Components.reserve(other.m_Components.size());
		for (auto& c : other.m_Components)
		{
			m_Components.push_back(c->Clone());
			auto& comp = m_Components.back();
			comp->m_Entity = this;
			comp->OnCreate();
		}
	}

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
			Renderer::Draw(sprite->m_Texture, m_Transform, sprite->m_Index);

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
