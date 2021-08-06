#pragma once

namespace Engine
{
	class Applicaiton
	{
	public:

		void Init();
		void Run();

		void Quit() { m_Quit = true; };

	protected:
		virtual void OnCreate() {};
		virtual void OnUpdate() {};
		virtual void OnDestroy() {};

	private:
		bool m_Quit = false;
	};
}