#pragma once
#include "Math\Math.h"
#include "Renderer\Color.h"
#include <string>
#include <rapidjson\document.h>

namespace Engine
{
	namespace JSON
	{
		bool Load(const std::string& filename, rapidjson::Document& document); 
		bool Get(const rapidjson::Value& value, const std::string& name, int& data);
		bool Get(const rapidjson::Value& value, const std::string& name, float& data);
		bool Get(const rapidjson::Value& value, const std::string& name, bool& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::string& data);
		bool Get(const rapidjson::Value& value, const std::string& name, Math::Vector2& data);
		bool Get(const rapidjson::Value& value, const std::string& name, Color& data);
	}
}