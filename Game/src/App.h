#pragma once
#include <Engine.h>

class App : public Engine::Application
{
protected:
	virtual void OnCreate() override;

	virtual void OnUpdate() override;
	virtual void OnDraw() override;

	Engine::Font m_Font;
};

class Player : public Engine::Drawable
{
public:
	virtual void OnCreate() override;
	virtual void Update(float dt) override;
};