#pragma once
#include "Core.h"
#include "Math\Math.h"
#include "Renderer\Texture.h"
#include "Component.h"
#include <vector>

namespace Engine
{
	class Scene;
}

namespace Engine
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(const Math::Transform& t);
		Entity(const std::string& tag, const Math::Transform& t);

		Entity(const Entity& other);

		virtual void OnCreate() {}
		virtual void Update();
		virtual void Draw();

		virtual void OnCollision(Entity* e);

		template<typename T, class... _Ty>
		T* AddComponent(_Ty&&... args)
		{
			if (HasComponent<T>())
				return nullptr;

			Scope<T> component = std::make_unique<T>(std::forward<_Ty>(args)...);
			component->m_Entity = this;
			m_Components.push_back(std::move(component));
			m_Components.back()->OnCreate();
			return dynamic_cast<T*>(m_Components.back().get());
		}

		template<typename T>
		T* GetComponent()
		{
			T* component = nullptr;
			for (auto& comp : m_Components)
				if (component = dynamic_cast<T*>(comp.get()))
					return component;
			return nullptr;
		}

		template<typename T>
		bool HasComponent()
		{
			return GetComponent<T>() != nullptr;
		}

	public:
		Math::Transform m_Transform;

	protected:
		Scene* m_Scene = nullptr;
		std::string m_Tag;
		std::vector<Scope<Component>> m_Components;

		friend Scene;
	};
}