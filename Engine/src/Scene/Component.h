#pragma once
#include "Core.h"
#include "Renderer\Texture.h"
#include "Math\Transform.h"
#include <varargs.h>
#include <vector>

namespace Engine
{
	class Entity;
}

namespace Engine
{
	class Component
	{
	public:
		virtual void OnCreate() {}
		virtual void Update() {}
		virtual void OnCollision(Entity* e) {}

		Math::Transform& Transform();

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

	public:
		Ref<Texture> m_Texture;
	};

	class CircleColliderComponent : public Component
	{
	public:
		CircleColliderComponent() = default;
		CircleColliderComponent(float r) :
			m_Radius(r)
		{}

	public:
		float m_Radius = 1.0f;
		
	};

	class AnimationComponent : public Component
	{
	public:
		AnimationComponent() = default;
		AnimationComponent(float frameTime, std::vector<int> frames) :
			m_FrameTime(frameTime), m_Frames(frames)
		{}

		virtual void Update() override;

	public:
		float m_FrameTime;
		std::vector<int> m_Frames;

	private:
		float m_FrameTimer = 0.0f;
		int m_Frame = 0;
	};
}