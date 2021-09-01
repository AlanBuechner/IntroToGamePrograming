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

		template<typename T, class... _Ty>
		Ref<T> AddPrefab(_Ty&&... args)
		{
			m_Prefabs.push_back(std::make_shared<T>(std::forward<_Ty>(args)...));
			return std::dynamic_pointer_cast<T>(m_Prefabs.back());
		}


		void Destroy(Entity* entity);
		Ref<Entity> GetPrefab(const std::string& name);

		void Load(const std::string& file);
		void Clear();

		void Update();
		void Draw();
	private:
		std::list<Ref<Entity>> m_Prefabs;
		std::list<Ref<Entity>> m_Entitys;
		std::list<std::list<Ref<Entity>>::const_iterator> m_ToDelete;

		std::string m_FileToLoad;
	};
}