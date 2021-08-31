#pragma once

namespace Engine
{
	class Color
	{
	public:
		Color() = default;
		Color(float r, float g, float b);

		float& operator [] (size_t index) { return (&r)[index]; }
		Color operator+(const Color& o) { return Color{ r + o.r, g + o.g, b + o.b }; }
		Color operator-(const Color& o) { return Color{ r - o.r, g - o.g, b - o.b }; }
		Color operator*(const Color& o) { return Color{ r * o.r, g * o.g, b * o.b }; }
		Color operator/(const Color& o) { return Color{ r / o.r, g / o.g, b / o.b }; }
		Color operator*(float s) { return Color{ r * s, g * s, b * s }; }
		Color operator/(float s) { return Color{ r / s, g / s, b / s }; }
		Color& operator+=(const Color& o) { return *this=(*this+o); }
		Color& operator-=(const Color& o) { return *this=(*this-o); }
		Color& operator*=(const Color& o) { return *this=(*this*o); }
		Color& operator/=(const Color& o) { return *this=(*this/o); }
		Color& operator*=(float s) { return *this=(*this*s); }
		Color& operator/=(float s) { return *this=(*this/s); }

	public:
		float r = 0.0f, g = 0.0f, b = 0.0f;
	};
}