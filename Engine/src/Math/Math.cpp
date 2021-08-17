#include "Math.h"
#include <random>
#include <limits>


namespace Math
{
	std::default_random_engine s_Engine;

	float lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}

	void SetRandomSeed(uint32_t seed)
	{
		
	}

	float Random()
	{
		std::uniform_real_distribution<float> distro{ 0, 1 };
		return distro(s_Engine);
	}

	float RandomRange(float min, float max)
	{
		std::uniform_real_distribution<float> distro{ min, max };
		return distro(s_Engine);
	}

	int RandomInt()
	{
		std::uniform_int_distribution<int> distro{ 0, std::numeric_limits<int>::max() };
		return distro(s_Engine);
	}

	int RandomIntRange(int min, int max)
	{
		std::uniform_int_distribution<int> distro{ min, max-1 };
		return distro(s_Engine);
	}



}