#include "SceneSerializer.h"
#include "Core.h"
#include "Entity.h"
#include "JSON.h"

namespace Engine
{
	void SceneSerializer::Deserealize(const std::string& file, Scene& scene)
	{
		scene.Clear();

		rapidjson::Document doc;
		JSON::Load(file, doc);

		if (doc.HasMember("Entitys") == false)
			return;

		auto& entitys = doc["Entitys"];
		for (rapidjson::SizeType e = 0; e < entitys.Size(); e++)
		{
			if (entitys[e].IsObject())
			{
				std::string tag;
				Math::Transform transform;
				bool prefab = false;

				JSON::Get(entitys[e], "Tag", tag);

				JSON::Get(entitys[e], "Position", transform.Position);
				JSON::Get(entitys[e], "Scale", transform.Scale);
				JSON::Get(entitys[e], "Rotation", transform.Rotation);

				JSON::Get(entitys[e], "Prefab", prefab);


				Ref<Entity> entity;
				if (prefab)
					entity = scene.AddPrefab<Entity>(tag, transform);
				else
					entity = scene.Instantiate<Entity>(tag, transform);

				auto& components = entitys[e]["Components"];
				for (rapidjson::SizeType c = 0; c < components.Size(); c++)
				{
					if (components[c].IsObject())
					{
						std::string type;
						if (JSON::Get(components[c], "Type", type))
						{
							if (type == "SpriteRendererComponent")
							{
								std::string texture;
								JSON::Get(components[c], "Texture", texture);
								auto sprite = entity->AddComponent<SpriteRendererComponent>(Texture::Create(texture));
								auto& atlis = sprite->m_Texture->m_Atlis;

								JSON::Get(components[c], "Rows", atlis.Rows);
								JSON::Get(components[c], "Cols", atlis.Cols);
								JSON::Get(components[c], "Index", sprite->m_Index);
							}
							else if (type == "TextRendererComponent")
							{
								auto textComp = entity->AddComponent<TextRendererComponent>();
								JSON::Get(components[c], "Text", textComp->m_Text);
								JSON::Get(components[c], "Color", textComp->m_Color);

								std::string font;
								JSON::Get(components[c], "Font", font);
								textComp->m_Font.Load(font, 16);
							}
							else if (type == "CircleColliderComponent")
							{
								float r = 1;
								JSON::Get(components[c], "Radius", r);
								entity->AddComponent<CircleColliderComponent>(r);
							}
							else if (type == "AnimationComponent")
							{
								float frameTime;
								std::vector<int> frames;

								JSON::Get(components[c], "FrameTime", frameTime);
								auto& f = components[c]["Frames"];

								for (rapidjson::SizeType i = 0; i < f.Size(); i++)
									frames.push_back(f[i].GetInt());
								
								entity->AddComponent<AnimationComponent>(frameTime, frames);
							}
							else if (type == "PlayerComponent")
							{
								auto player = entity->AddComponent<PlayerComponent>();
							}
							else if (type == "SpikeComponent")
							{
								auto enemy = entity->AddComponent<SpikeComponent>();

								JSON::Get(components[c], "Speed", enemy->m_Speed);
							}
							else if (type == "PickupComponent")
							{
								auto coin = entity->AddComponent<PickupComponent>();
								JSON::Get(components[c], "Speed", coin->m_Speed);
							}
							else if (type == "ManegerComponent")
							{
								auto maneger = entity->AddComponent<ManegerComponent>();
								JSON::Get(components[c], "SpawnRate", maneger->m_SpawnRate);
							}
						}
					}
				}
			}
		}
	}
}
