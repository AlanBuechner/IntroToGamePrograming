#pragma once
#include <memory>
#include <cstdint>
#include <string>

namespace Engine
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;
}