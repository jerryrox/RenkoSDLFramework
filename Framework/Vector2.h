#pragma once

#ifndef _VECTOR2_
#define _VECTOR2_

struct Vector2
{
public:
	// X vector value
	float x;

	// Y vector value
	float y;
	
	Vector2();
	Vector2(float x, float y);

	// Returns the up vector of length 1.
	static Vector2 Up();

	// Returns the down vector of length 1.
	static Vector2 Down();

	// Returns the left vector of length 1.
	static Vector2 Left();

	// Returns the right vector of length 1.
	static Vector2 Right();

	// Normalizes this vector's values.
	void Normalize();

	// Returns a new Vector2 with normalized vector.
	Vector2 GetNormalized();

	// Returns the length of the vector.
	float GetMagnitude();

	// Returns the squared length of the vector.
	float GetSqrMagnitude();

	void operator+(Vector2 other);
	void operator-(Vector2 other);
	void operator*(float scale);
	void operator/(float scale);
};

#endif