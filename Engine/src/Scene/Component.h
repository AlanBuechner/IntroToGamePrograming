#pragma once
#include "Core.h"
#include "Renderer\Texture.h"
#include "Math\Transform.h"
#include "Renderer\Font.h"
#include "Renderer\Color.h"
#include <varargs.h>
#include <vector>

#define CLONE(name) virtual Scope<Component> Clone() override { return std::make_unique<name>(*this); }

namespace Engine
{
	class Entity;
}

namespace Engine
{
	class Component
	{
	public:
		virtual Scope<Component> Clone() = 0;

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
		CLONE(SpriteRendererComponent);

		SpriteRendererComponent() = default;
		SpriteRendererComponent(Ref<Texture> texture) :
			m_Texture(texture)
		{}

	public:
		Ref<Texture> m_Texture;
		int m_Index = 0;
	};

	class TextRendererComponent : public Component
	{
	public:
		CLONE(TextRendererComponent);
		TextRendererComponent() = default;
		TextRendererComponent(const std::string& text) :
			m_Text(text)
		{}

	public:
		std::string m_Text;
		Color m_Color;
		Font m_Font;
	};

	class CircleColliderComponent : public Component
	{
	public:
		CLONE(CircleColliderComponent);
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
		CLONE(AnimationComponent);
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

	class PlayerComponent : public Component
	{
	public:
		CLONE(PlayerComponent);

	private:
		virtual void Update() override;
		virtual void OnCollision(Entity* e) override;

	private:
		float m_DownSpeed = 0.0f;
	};

	class SpikeComponent : public Component
	{
	public:
		CLONE(SpikeComponent);
	private:
		virtual void Update() override;

	public:
		float m_Speed = 100.0f;
	};

	class PickupComponent : public Component
	{
	public:
		CLONE(PickupComponent);
		virtual void Update() override;
		virtual void OnCollision(Entity* e) override;

	public:
		float m_Speed = 100.0f;
	};

	class ManegerComponent : public Component
	{
	public:
		CLONE(ManegerComponent);
		virtual void Update() override;

	public:
		float m_SpawnRate;

	private:
		float m_SpawnTimer = 0.0f;
	};

}