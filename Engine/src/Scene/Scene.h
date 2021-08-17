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

		template<typename T, class... _Ty>
		Ref<T> Instantiate(_Ty&&... args)
		{
			m_Entitys.push_back(std::make_shared<T>(std::forward<_Ty>(args)...));
			Ref<T> entity = std::dynamic_pointer_cast<T>(m_Entitys.back());
			entity->m_Scene = this;
			entity->OnCreate();
			return entity;
		}

		void Update(float dt);
		void Draw();
	private:
		std::list<Ref<Entity>> m_Entitys;
	};
}