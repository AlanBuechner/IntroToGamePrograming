#pragma once
#include "Vector2.h"

namespace Math
{
	struct Transform
	{
		Vector2 Position = { 0.0f, 0.0f };
		Vector2 Scale = { 1.0f, 1.0f };
		float Rotation = 0.0f;
	};
}