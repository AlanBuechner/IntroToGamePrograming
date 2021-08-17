#pragma once
#include "Core.h"
#include "Renderer\Texture.h"

namespace Engine
{
	class Entity;
}

namespace Engine
{
	class Component
	{
	public:
		virtual void OnCreate() {};
		virtual void Update() {};

	public:
		Entity* m_Entity = nullptr;
	};

	// Sprite Renderer Component
	class SpriteRendererComponent : public Component
	{
	public:
		SpriteRendererComponent() = default;
		SpriteRendererComponent(Ref<Texture> texture) :
			m_Texture(texture)
		{}
		Ref<Texture> m_Texture;
	};
}