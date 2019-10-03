#pragma once

#ifndef _RANDOM_
#define _RANDOM_

#include <random>
#include <time.h>
#include <stdlib.h>

class Random
{
public:
	static void Initialize();

	// Returns a random value between 0 and 1, excluding 1.
	static double Range01();

	// Returns a random float value between min and max, excluding max.
	static float Range(float min, float max);

	// Returns a random int value between min and max, excluding max.
	static int Range(int min, int max);
};

#endif