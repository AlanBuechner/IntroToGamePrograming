#include "Scene.h"
#include "Entity.h"

namespace Engine
{
    void Scene::Destroy(Entity* entity)
    {
        for (auto e = m_ToDelete.begin(); e != m_ToDelete.end(); e++)
            if ((*e)->get() == entity)
                return;
        
        for (auto e = m_Entitys.begin(); e != m_Entitys.end(); e++)
            if (e->get() == entity)
                m_ToDelete.push_back(e);
    }

    void Scene::Update()
    {
        std::vector<CircleColliderComponent*> collidableEntitys;
        collidableEntitys.reserve(m_Entitys.size());

        // update components
        for (auto& e : m_Entitys)
        {
            e->Update();
            auto comp = e->GetComponent<CircleColliderComponent>();
            if (comp)
                collidableEntitys.push_back(comp);
        }

        // Collision Ditection
        if (collidableEntitys.size() >= 2)
        {
            for (uint32_t i = 0; i < collidableEntitys.size() - 1; i++)
            {
                auto& e1 = collidableEntitys[i];
                auto& s1 = e1->Transform().Scale;
                float r1 = e1->m_Radius * std::max(s1.x, s1.y);
                for (int j = i + 1; j < collidableEntitys.size(); j++)
                {
                    auto& e2 = collidableEntitys[j];
                    auto& s2 = e1->Transform().Scale;
                    float r2 = e1->m_Radius * std::max(s2.x, s2.y);

                    float dist = (e2->Transform().Position - e1->Transform().Position).LengthSqr();

                    if (dist <= r1 * r1 + r2 * r2)
                    {
                        e1->m_Entity->OnCollision(e2->m_Entity);
                        e2->m_Entity->OnCollision(e1->m_Entity);
                    }
                }
            }
        }


        for (auto& e : m_ToDelete)
        {
            m_Entitys.erase(e);
        }
        m_ToDelete.clear();
    }

    void Scene::Draw()
    {
        for (auto e : m_Entitys)
        {
            e->Draw();
        }
    }
    
}