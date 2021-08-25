#pragma once
#include "Scene\Scene.h"
#include "Scene\Entity.h"

namespace Engine
{
	class Application
	{
		static Application* s_Instance;
	public:
		static Application* Get() { return s_Instance; }
		static Scene& GetScene() { return s_Instance->m_Scene; }

		void Init();
		void Run();

		void Quit() { m_Quit = true; };

	protected:
		virtual void OnCreate() {};
		virtual void OnUpdate() {};
		virtual void OnDraw() {};
		virtual void OnDestroy() {};

	private:
		bool m_Quit = false;

		Scene m_Scene;
	};
}