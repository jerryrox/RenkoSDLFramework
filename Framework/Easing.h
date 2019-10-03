#pragma once

#ifndef _EASING_
#define _EASING_

#include "EaseType.h"

#include <map>
#include <functional>

#define Pi 3.14159265358979323846f
#define EaseHandler	std::function<float(float, float, float, float)>

class Easing
{
private:
	static std::map<EaseType, EaseHandler>* Handlers;

public:
	static void Initialize();

	static void Destroy();

	static float Ease(EaseType type, float t, float b, float c, float d);

	static float Linear(float t, float b, float c, float d);

	static float EaseOut(float t, float b, float c, float d);

	static float EaseIn(float t, float b, float c, float d);

	static float ExpoEaseOut(float t, float b, float c, float d);

	static float ExpoEaseIn(float t, float b, float c, float d);

	static float ExpoEaseInOut(float t, float b, float c, float d);

	static float ExpoEaseOutIn(float t, float b, float c, float d);

	static float CircEaseOut(float t, float b, float c, float d);

	static float CircEaseIn(float t, float b, float c, float d);

	static float CircEaseInOut(float t, float b, float c, float d);

	static float CircEaseOutIn(float t, float b, float c, float d);

	static float QuadEaseOut(float t, float b, float c, float d);

	static float QuadEaseIn(float t, float b, float c, float d);

	static float QuadEaseInOut(float t, float b, float c, float d);

	static float QuadEaseOutIn(float t, float b, float c, float d);

	static float SineEaseOut(float t, float b, float c, float d);

	static float SineEaseIn(float t, float b, float c, float d);

	static float SineEaseInOut(float t, float b, float c, float d);

	static float SineEaseOutIn(float t, float b, float c, float d);

	static float CubicEaseOut(float t, float b, float c, float d);

	static float CubicEaseIn(float t, float b, float c, float d);

	static float CubicEaseInOut(float t, float b, float c, float d);

	static float CubicEaseOutIn(float t, float b, float c, float d);

	static float QuartEaseOut(float t, float b, float c, float d);

	static float QuartEaseIn(float t, float b, float c, float d);

	static float QuartEaseInOut(float t, float b, float c, float d);

	static float QuartEaseOutIn(float t, float b, float c, float d);

	static float QuintEaseOut(float t, float b, float c, float d);

	static float QuintEaseIn(float t, float b, float c, float d);

	static float QuintEaseInOut(float t, float b, float c, float d);

	static float QuintEaseOutIn(float t, float b, float c, float d);

	static float ElasticEaseOut(float t, float b, float c, float d);

	static float ElasticEaseIn(float t, float b, float c, float d);

	static float ElasticEaseInOut(float t, float b, float c, float d);

	static float ElasticEaseOutIn(float t, float b, float c, float d);

	static float BounceEaseOut(float t, float b, float c, float d);

	static float BounceEaseIn(float t, float b, float c, float d);

	static float BounceEaseInOut(float t, float b, float c, float d);

	static float BounceEaseOutIn(float t, float b, float c, float d);

	static float BackEaseOut(float t, float b, float c, float d);

	static float BackEaseIn(float t, float b, float c, float d);

	static float BackEaseInOut(float t, float b, float c, float d);

	static float BackEaseOutIn(float t, float b, float c, float d);
};

#endif // !_EASING_
