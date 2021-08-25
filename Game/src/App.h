#pragma once
#include <Engine.h>

class App : public Engine::Application
{
protected:
	virtual void OnCreate() override;

	virtual void OnUpdate() override;
	virtual void OnDraw() override;
};

class PlayerComponent : public Engine::Component
{
	static PlayerComponent* s_Instance;

public:
	static PlayerComponent* Get() { return s_Instance; }

private:
	virtual void OnCreate() override;
	virtual void Update() override;
	virtual void OnCollision(Engine::Entity* e) override;

private:
	float m_Speed = 300.0f;
	float m_RotSpeed = 270.0f;

	float m_FireRate = 0.5f;
	float m_FireTimer = 0.0f;
};

class BulletComponent : public Engine::Component
{
private:
	virtual void OnCreate() override;
	virtual void Update() override;

private:
	Math::Vector2 m_Direction;
	float m_Speed = 500.0f;
};

class EnemyComponent : public Engine::Component
{
private:
	virtual void OnCreate() override;
	virtual void Update() override;
	virtual void OnCollision(Engine::Entity* e) override;

public:
	static void Spawn();

private:
	Engine::Entity* m_Target = nullptr;
	float m_Speed = 100.0f;
};