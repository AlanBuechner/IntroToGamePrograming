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

	float alerp(float a, float b, float t)
	{
		float result;
		float diff = b - a;
		if (diff < -180.f)
		{
			// lerp upwards past 360
			b += 360.f;
			result = lerp(a, b, t);
			if (result >= 360.f)
			{
				result -= 360.f;
			}
		}
		else if (diff > 180.f)
		{
			// lerp downwards past 0
			b -= 360.f;
			result = lerp(a, b, t);
			if (result < 0.f)
			{
				result += 360.f;
			}
		}
		else
		{
			// straight lerp
			result = lerp(a, b, t);
		}

		return result;
	}

	float RadToDeg(float rad) { return rad * 180.0f / 3.14f; }

	float DegToRad(float deg) { return deg * 3.14f / 180.0f; }

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