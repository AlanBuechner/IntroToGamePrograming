#pragma once
#include "Core.h"
#include <list>

namespace Engine
{
	class Entity;
}

namespace Engine
{
	class Scene
	{
	public:

		template<typename T>
		Ref<T> Instantiate()
		{
			m_Entitys.push_back(std::make_shared<T>());
			Ref<T> entity = std::dynamic_pointer_cast<T>(m_Entitys.back());
			entity->OnCreate();
			return entity;
		}

		void Update(float dt);
		void Draw();
	private:
		std::list<Ref<Entity>> m_Entitys;
	};
}