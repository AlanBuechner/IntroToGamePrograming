#include "Audio.h"
#include <fmod.h>
#include <fmod.hpp>
#include "JSON.h"

FMOD::System* Engine::Audio::s_System;
std::map<std::string, FMOD::Sound*> Engine::Audio::s_Clips;


namespace Engine
{
	void Audio::Init()
	{
		FMOD::System_Create(&s_System);
		s_System->init(32, FMOD_INIT_NORMAL, nullptr);

		rapidjson::Document doc;
		JSON::Load("Resorces.json", doc);

		auto& audioClips = doc["Audio"];
		for (rapidjson::SizeType i = 0; i < audioClips.Size(); i++)
		{
			auto& clip = audioClips[i];
			if (clip.IsObject())
			{
				std::string name;
				std::string file;

				JSON::Get(clip, "Name", name);
				JSON::Get(clip, "File", file);
				AddAudio(name, file);
			}
		}

	}

	void Audio::Destroy()
	{
		for (auto& clip : s_Clips) 
		{ 
			clip.second->release(); 
		}
		
		s_Clips.clear();
		s_System->close();
		s_System->release();
	}

	void Audio::Update()
	{
		s_System->update();
	}

	void Audio::AddAudio(const std::string& name, const std::string& filename)
	{
		if(s_Clips.find(name) == s_Clips.end())
		{ 
			FMOD::Sound* sound{ nullptr };
			s_System->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
			s_Clips[name] = sound;
		}
	}

	void Audio::PlayAudio(const std::string& name)
	{
		auto iter = s_Clips.find(name);
		if (iter != s_Clips.end())
		{ 
			FMOD::Sound* sound = iter->second; 
			sound->setMode(FMOD_LOOP_OFF);
			FMOD::Channel* channel;
			s_System->playSound(sound, 0, false, &channel);
		}
	}



}