#pragma once
#include "Core.h"
#include "Renderer\Texture.h"
#include "Math\Transform.h"
#include "Renderer\Font.h"
#include "Renderer\Color.h"
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

	class TextRendererComponent : public Component
	{
	public:
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

	class PlayerComponent : public Component
	{
		static PlayerComponent* s_Instance;

	public:
		static PlayerComponent* Get() { return s_Instance; }

	private:
		virtual void OnCreate() override;
		virtual void Update() override;
		virtual void OnCollision(Entity* e) override;

	public:
		float m_Speed = 300.0f;
		float m_RotSpeed = 270.0f;

		float m_FireRate = 0.5f;

	private:
		float m_FireTimer = 0.0f;
	};

	class BulletComponent : public Component
	{
	private:
		virtual void OnCreate() override;
		virtual void Update() override;

	private:
		Math::Vector2 m_Direction;
		float m_Speed = 500.0f;
	};

	class EnemyComponent : public Component
	{
	private:
		virtual void OnCreate() override;
		virtual void Update() override;
		virtual void OnCollision(Entity* e) override;

	public:
		static void Spawn();

	public:
		float m_Speed = 100.0f;

	private:
		Entity* m_Target = nullptr;
	};

	class PickupComponent : public Component
	{
	public:
		virtual void OnCollision(Entity* e) override;
	};



}