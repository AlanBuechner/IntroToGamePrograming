#include "JSON.h"
#include <iostream>
#include <fstream>
#include <rapidjson\istreamwrapper.h>

namespace Engine
{
	bool JSON::Load(const std::string& filename, rapidjson::Document& document)
	{
		bool success = false;

		std::ifstream stream;
		stream.open(filename);
		if (stream.is_open())
		{
			rapidjson::IStreamWrapper istream(stream);
			document.ParseStream(istream);
			success = document.IsObject();
		}

		return success;
	}

	bool JSON::Get(const rapidjson::Value& value, const std::string& name, int& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsInt() == false)
			return false;
		// set data
		data = value[name.c_str()].GetInt();
		return true;
	}

	bool JSON::Get(const rapidjson::Value& value, const std::string& name, float& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsFloat() == false)
			return false;
		// set data
		data = value[name.c_str()].GetFloat();
		return true;
	}

	bool JSON::Get(const rapidjson::Value& value, const std::string& name, bool& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsBool() == false)
			return false;
		// set data
		data = value[name.c_str()].GetBool();
		return true;
	}

	bool JSON::Get(const rapidjson::Value& value, const std::string& name, std::string& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsString() == false)
			return false;
		// set data
		data = value[name.c_str()].GetString();
		return true;
	}

	bool JSON::Get(const rapidjson::Value& value, const std::string& name, Math::Vector2& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false)
			return false;
		// set data
		auto& array = value[name.c_str()];
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (array[i].IsNumber())
				data[i] = array[i].GetFloat();
		}

		return true;
	}

	bool JSON::Get(const rapidjson::Value& value, const std::string& name, Color& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false)
			return false;
		// set data
		auto& array = value[name.c_str()];
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (array[i].IsNumber())
				data[i] = array[i].GetFloat();
		}

		return true;
	}

}