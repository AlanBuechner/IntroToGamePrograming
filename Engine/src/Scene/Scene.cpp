#include "Scene.h"
#include "Entity.h"

namespace Engine
{

    void Scene::Update(float dt)
    {
        for (auto e : m_Entitys)
        {
            e->Update(dt);
        }
    }

    void Scene::Draw()
    {
        for (auto e : m_Entitys)
        {
            e->Draw();
        }
    }
    
}