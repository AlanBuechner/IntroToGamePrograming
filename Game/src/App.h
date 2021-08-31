#pragma once
#include <Engine.h>

class App : public Engine::Application
{
protected:
	virtual void OnCreate() override;

	virtual void OnUpdate() override;
	virtual void OnDraw() override;
};