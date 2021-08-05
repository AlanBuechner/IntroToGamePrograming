#pragma once
#include <cmath>

namespace Math
{
	class Vector2
	{
	public:

		Vector2() = default;
		Vector2(float x, float y) :
			x(x), y(y) {}
		Vector2(int x, int y) :
			x((float)x), y((float)y) {}

		void Set(float x, float y) { this->x = x; this->y = y; }

		float& operator [] (size_t index) { return (&x)[index]; }
		const float& operator [] (size_t index) const { return (&x)[index]; }
		Vector2 operator + (const Vector2& v) const { return { x + v.x, y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return { x - v.x, y - v.y }; }
		Vector2 operator * (const Vector2& v) const { return { x * v.x, y * v.y }; }
		Vector2 operator / (const Vector2& v) const { return { x / v.x, y / v.y }; }
		Vector2 operator + (float s) const { return { x + s, y + s }; }
		Vector2 operator - (float s) const { return { x - s, y - s }; }
		Vector2 operator * (float s) const { return { x * s, y * s }; }
		Vector2 operator / (float s) const { return { x / s, y / s }; }
		Vector2& operator += (const Vector2& v) { return *this=(*this + v); }
		Vector2& operator -= (const Vector2& v) { return *this=(*this - v); }
		Vector2& operator *= (const Vector2& v) { return *this=(*this * v); }
		Vector2& operator /= (const Vector2& v) { return *this=(*this - v); }
		Vector2& operator += (float s) { return *this = (*this + s); }
		Vector2& operator -= (float s) { return *this = (*this - s); }
		Vector2& operator *= (float s) { return *this = (*this * s); }
		Vector2& operator /= (float s) { return *this = (*this / s); }
		Vector2 operator - () const { return { -x, -y }; }
		bool operator == (const Vector2& v) const { return x == v.x && y == v.y; }
		bool operator != (const Vector2& v) const { return !(*this == v); }
		float LengthSqr() const { return x * x + y * y; }
		float Length() const { return sqrt(LengthSqr()); }
		Vector2 Normalized() const { return *this / Length(); }
		void Normalize() { *this /= Length(); }
		float Angle() const { return atan2(y, x); }
		static float Distance(const Vector2& v1, const Vector2& v2) { return (v2 - v1).Length(); }
		static Vector2 Rotate(const Vector2& v, float radians) {
			return{	v.x * cos(radians) - v.y * sin(radians),
					v.x * sin(radians) + v.y * cos(radians) };
		}

		void Wrap(float wx, float wy)
		{
			if (x < 0) x = wx;
			if (x > wx) x = 0;
			if (y < 0) y = wy;
			if (y > wy) y = 0;
		}

	public:
		float x = 0, y = 0;

		static const Vector2 Left;
		static const Vector2 Right;
		static const Vector2 Up;
		static const Vector2 Down;
		static const Vector2 One;
		static const Vector2 Zero;
	};
}