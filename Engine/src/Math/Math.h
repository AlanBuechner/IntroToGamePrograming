#pragma once
#include "Transform.h"
#include "Vector2.h"
#include "Core.h"

namespace Math
{
	float lerp(float a, float b, float t);
	float alerp(float a, float b, float t);

	float RadToDeg(float rad);
	float DegToRad(float deg);

	void SetRandomSeed(uint32_t seed);
	float Random();
	float RandomRange(float min, float max);
	int RandomInt();
	int RandomIntRange(int min, int max);
}