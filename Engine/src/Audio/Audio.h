#pragma once
#include <Core.h>
#include <fmod.hpp>
#include <map>

namespace Engine
{
	class Audio
	{
	public:
		static void Init();
		static void Destroy();

		static void Update();

		static void AddAudio(const std::string& name, const std::string& filename); 
		static void PlayAudio(const std::string& name);

	private:
		static FMOD::System* s_System;
		static std::map<std::string, FMOD::Sound*> s_Clips;
	};
}