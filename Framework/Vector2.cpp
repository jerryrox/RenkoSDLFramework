#include "Vector2.h"

#include <math.h>

Vector2::Vector2() : Vector2(0, 0) {}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2 Vector2::Up() { return Vector2(0, -1); }

Vector2 Vector2::Down() { return Vector2(0, 1); }

Vector2 Vector2::Left() { return Vector2(-1, 0); }

Vector2 Vector2::Right() { return Vector2(0, 1); }

void Vector2::Normalize()
{
	float magnitude = GetMagnitude();
	x /= magnitude;
	y /= magnitude;
}

Vector2 Vector2::GetNormalized()
{
	float magnitude = GetMagnitude();
	return Vector2(x / magnitude, y / magnitude);
}

inline float Vector2::GetMagnitude() { return sqrtf(GetSqrMagnitude()); }

inline float Vector2::GetSqrMagnitude() { return x * x + y * y; }

void Vector2::operator+(Vector2 other)
{
	x += other.x;
	y += other.y;
}

void Vector2::operator-(Vector2 other)
{
	x -= other.x;
	y -= other.y;
}

void Vector2::operator*(float scale)
{
	x *= scale;
	y *= scale;
}

void Vector2::operator/(float scale)
{
	x /= scale;
	y /= scale;
}