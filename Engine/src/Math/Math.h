#pragma once
#include "Transform.h"
#include "Vector2.h"
#include "Core.h"

namespace Math
{
	float lerp(float a, float b, float t);

	void SetRandomSeed(uint32_t seed);
	float Random();
	float RandomRange(float min, float max);
	int RandomInt();
	int RandomIntRange(int min, int max);
}