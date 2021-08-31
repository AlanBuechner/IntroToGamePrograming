#pragma once
#include "Core.h"
#include <Scene\Scene.h>

namespace Engine
{
	class SceneSerializer
	{
	public:
		static void Deserealize(const std::string& file, Scene& scene);
	};
}