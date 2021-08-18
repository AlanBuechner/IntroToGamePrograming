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
	virtual void Update() override;

private:
	float m_Speed = 100.0f;
	float m_RotSpeed = 270.0f;
};