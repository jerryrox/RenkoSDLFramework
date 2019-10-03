#include "Random.h"

void Random::Initialize()
{
	srand((unsigned int)time(0));
}

double Random::Range01()
{
	static const double scale = 1.0 / (RAND_MAX + 1.0);
	return rand() * scale;
}

float Random::Range(float min, float max)
{
	return (float)((max - min) * Range01() + min);
}

int Random::Range(int min, int max)
{
	return (int)((max - min) * Range01() + min);
}