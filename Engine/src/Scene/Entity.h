#pragma once
#include "Core.h"
#include "Math\Math.h"
#include "Renderer\Texture.h"

namespace Engine
{
	class Scene;
}

namespace Engine
{
	class Entity
	{
	public:
		virtual void OnCreate() {}
		virtual void Update(float dt) {}
		virtual void Draw() {}

	protected:
		Math::Transform m_Transform;

		friend Scene;
	};

	class Drawable : public Entity
	{
	public:
		virtual void Draw() override;

	protected:
		Ref<Texture> m_Texture;
	};
}