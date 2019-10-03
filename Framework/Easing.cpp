#include "Easing.h"

std::map<EaseType, EaseHandler>* Easing::Handlers = 0;

void Easing::Initialize()
{
	if (Handlers != 0)
		return;

	Handlers = new std::map<EaseType, EaseHandler>();
	Handlers->emplace(EaseType::BackEaseIn, BackEaseIn);
	Handlers->emplace(EaseType::BackEaseInOut, BackEaseInOut);
	Handlers->emplace(EaseType::BackEaseOut, BackEaseOut);
	Handlers->emplace(EaseType::BackEaseOutIn, BackEaseOutIn);
	Handlers->emplace(EaseType::BounceEaseIn, BounceEaseIn);
	Handlers->emplace(EaseType::BounceEaseInOut, BounceEaseInOut);
	Handlers->emplace(EaseType::BounceEaseOut, BounceEaseOut);
	Handlers->emplace(EaseType::BounceEaseOutIn, BounceEaseOutIn);
	Handlers->emplace(EaseType::CircEaseIn, CircEaseIn);
	Handlers->emplace(EaseType::CircEaseInOut, CircEaseInOut);
	Handlers->emplace(EaseType::CircEaseOut, CircEaseOut);
	Handlers->emplace(EaseType::CircEaseOutIn, CircEaseOutIn);
	Handlers->emplace(EaseType::CubicEaseIn, CubicEaseIn);
	Handlers->emplace(EaseType::CubicEaseInOut, CubicEaseInOut);
	Handlers->emplace(EaseType::CubicEaseOut, CubicEaseOut);
	Handlers->emplace(EaseType::CubicEaseOutIn, CubicEaseOutIn);
	Handlers->emplace(EaseType::EaseIn, EaseIn);
	Handlers->emplace(EaseType::EaseOut, EaseOut);
	Handlers->emplace(EaseType::ElasticEaseIn, ElasticEaseIn);
	Handlers->emplace(EaseType::ElasticEaseInOut, ElasticEaseInOut);
	Handlers->emplace(EaseType::ElasticEaseOut, ElasticEaseOut);
	Handlers->emplace(EaseType::ElasticEaseOutIn, ElasticEaseOutIn);
	Handlers->emplace(EaseType::ExpoEaseIn, ExpoEaseIn);
	Handlers->emplace(EaseType::ExpoEaseInOut, ExpoEaseInOut);
	Handlers->emplace(EaseType::ExpoEaseOut, ExpoEaseOut);
	Handlers->emplace(EaseType::ExpoEaseOutIn, ExpoEaseOutIn);
	Handlers->emplace(EaseType::Linear, Linear);
	Handlers->emplace(EaseType::QuadEaseIn, QuadEaseIn);
	Handlers->emplace(EaseType::QuadEaseInOut, QuadEaseInOut);
	Handlers->emplace(EaseType::QuadEaseOut, QuadEaseOut);
	Handlers->emplace(EaseType::QuadEaseOutIn, QuadEaseOutIn);
	Handlers->emplace(EaseType::QuartEaseIn, QuartEaseIn);
	Handlers->emplace(EaseType::QuartEaseInOut, QuartEaseInOut);
	Handlers->emplace(EaseType::QuartEaseOut, QuartEaseOut);
	Handlers->emplace(EaseType::QuartEaseOutIn, QuartEaseOutIn);
	Handlers->emplace(EaseType::QuintEaseIn, QuintEaseIn);
	Handlers->emplace(EaseType::QuintEaseInOut, QuintEaseInOut);
	Handlers->emplace(EaseType::QuintEaseOut, QuintEaseOut);
	Handlers->emplace(EaseType::QuintEaseOutIn, QuintEaseOutIn);
	Handlers->emplace(EaseType::SineEaseIn, SineEaseIn);
	Handlers->emplace(EaseType::SineEaseInOut, SineEaseInOut);
	Handlers->emplace(EaseType::SineEaseOut, SineEaseOut);
	Handlers->emplace(EaseType::SineEaseOutIn, SineEaseOutIn);
}

void Easing::Destroy()
{
	if (Handlers == 0)
		return;

	delete Handlers;
	Handlers = 0;
}

float Easing::Ease(EaseType type, float t, float b, float c, float d)
{
	return Handlers->at(type)(t, b, c, d);
}

float Easing::Linear(float t, float b, float c, float d) {
	return c * t + b;
}

float Easing::EaseOut(float t, float b, float c, float d) {
	return QuadEaseOut(t, b, c, d);
}

float Easing::EaseIn(float t, float b, float c, float d) {
	return QuadEaseIn(t, b, c, d);
}

float Easing::ExpoEaseOut(float t, float b, float c, float d) {
	return (t == 1) ? b + c : c * (-powf(2, -10 * t) + 1) + b;
}

float Easing::ExpoEaseIn(float t, float b, float c, float d) {
	return (t == 0) ? b : c * powf(2, 10 * (t - 1)) + b;
}

float Easing::ExpoEaseInOut(float t, float b, float c, float d) {
	if (t == 0)
		return b;

	if (t == 1)
		return b + c;

	if ((t *= 2) < 1)
		return c * 0.5f * powf(2, 10 * (t - 1)) + b;

	return c * 0.5f * (-powf(2, -10 * --t) + 2) + b;
}

float Easing::ExpoEaseOutIn(float t, float b, float c, float d) {
	if (t < 0.5f)
		return ExpoEaseOut(t * 2, b, c  * 0.5f, d);

	return ExpoEaseIn((t * 2) - 1, b + c * 0.5f, c * 0.5f, d);
}

float Easing::CircEaseOut(float t, float b, float c, float d) {
	return c * sqrtf(1 - (t = t - 1) * t) + b;
}

float Easing::CircEaseIn(float t, float b, float c, float d) {
	return -c * (sqrtf(1 - t * t) - 1) + b;
}

float Easing::CircEaseInOut(float t, float b, float c, float d) {
	if ((t *= 2) < 1)
		return -c * 0.5f * (sqrtf(1 - t * t) - 1) + b;

	return c * 0.5f * (sqrtf(1 - (t -= 2) * t) + 1) + b;
}

float Easing::CircEaseOutIn(float t, float b, float c, float d) {
	if (t < 0.5f)
		return CircEaseOut(t * 2, b, c * 0.5f, d);

	return CircEaseIn((t * 2) - 1, b + c * 0.5f, c * 0.5f, d);
}

float Easing::QuadEaseOut(float t, float b, float c, float d) {
	return -c * t * (t - 2) + b;
}

float Easing::QuadEaseIn(float t, float b, float c, float d) {
	return c * t * t + b;
}

float Easing::QuadEaseInOut(float t, float b, float c, float d) {
	if ((t *= 2) < 1)
		return c * 0.5f * t * t + b;

	return -c * 0.5f * ((--t) * (t - 2) - 1) + b;
}

float Easing::QuadEaseOutIn(float t, float b, float c, float d) {
	if (t < 0.5f)
		return QuadEaseOut(t * 2, b, c * 0.5f, d);

	return QuadEaseIn((t * 2) - 1, b + c * 0.5f, c * 0.5f, d);
}

float Easing::SineEaseOut(float t, float b, float c, float d) {
	return c * sinf(t * (Pi * 0.5f)) + b;
}

float Easing::SineEaseIn(float t, float b, float c, float d) {
	return -c * cosf(t * (Pi * 0.5f)) + c + b;
}

float Easing::SineEaseInOut(float t, float b, float c, float d) {
	if ((t *= 2) < 1)
		return SineEaseIn(t, b, c*0.5f, d);
	return SineEaseOut(t - 1, b + c * 0.5f, c*0.5f, d);
}

float Easing::SineEaseOutIn(float t, float b, float c, float d) {
	if (t < 0.5f)
		return SineEaseOut(t * 2, b, c * 0.5f, d);

	return SineEaseIn((t * 2) - 1, b + c * 0.5f, c * 0.5f, d);
}

float Easing::CubicEaseOut(float t, float b, float c, float d) {
	return c * ((t = t - 1) * t * t + 1) + b;
}

float Easing::CubicEaseIn(float t, float b, float c, float d) {
	return c * t * t * t + b;
}

float Easing::CubicEaseInOut(float t, float b, float c, float d) {
	if ((t *= 2) < 1)
		return c * 0.5f * t * t * t + b;

	return c * 0.5f * ((t -= 2) * t * t + 2) + b;
}

float Easing::CubicEaseOutIn(float t, float b, float c, float d) {
	if (t < 0.5f)
		return CubicEaseOut(t * 2, b, c * 0.5f, d);

	return CubicEaseIn((t * 2) - 1, b + c * 0.5f, c * 0.5f, d);
}

float Easing::QuartEaseOut(float t, float b, float c, float d) {
	return -c * ((t = t - 1) * t * t * t - 1) + b;
}

float Easing::QuartEaseIn(float t, float b, float c, float d) {
	return c * t * t * t * t + b;
}

float Easing::QuartEaseInOut(float t, float b, float c, float d) {
	if ((t *= 2) < 1)
		return c * 0.5f * t * t * t * t + b;

	return -c * 0.5f * ((t -= 2) * t * t * t - 2) + b;
}

float Easing::QuartEaseOutIn(float t, float b, float c, float d) {
	if (t < 0.5f)
		return QuartEaseOut(t * 2, b, c * 0.5f, d);

	return QuartEaseIn((t * 2) - 1, b + c * 0.5f, c * 0.5f, d);
}

float Easing::QuintEaseOut(float t, float b, float c, float d) {
	return c * ((t = t - 1) * t * t * t * t + 1) + b;
}

float Easing::QuintEaseIn(float t, float b, float c, float d) {
	return c * t * t * t * t * t + b;
}

float Easing::QuintEaseInOut(float t, float b, float c, float d) {
	if ((t *= 2) < 1)
		return c * 0.5f * t * t * t * t * t + b;
	return c * 0.5f * ((t -= 2) * t * t * t * t + 2) + b;
}

float Easing::QuintEaseOutIn(float t, float b, float c, float d) {
	if (t < 0.5f)
		return QuintEaseOut(t * 2, b, c * 0.5f, d);
	return QuintEaseIn((t * 2) - 1, b + c * 0.5f, c * 0.5f, d);
}

float Easing::ElasticEaseOut(float t, float b, float c, float d) {
	if (t == 1)
		return b + c;

	float p = d * 0.3f;
	float s = p * 0.25f;

	return (c * powf(2, -10 * t) * sinf((t * d - s) * (2 * Pi) / p) + c + b);
}

float Easing::ElasticEaseIn(float t, float b, float c, float d) {
	if (t == 1)
		return b + c;

	float p = d * 0.3f;
	float s = p * 0.25f;

	return -(c * powf(2, 10 * (t -= 1)) * sinf((t * d - s) * (2 * Pi) / p)) + b;
}

float Easing::ElasticEaseInOut(float t, float b, float c, float d) {
	if ((t *= 2) == 2)
		return b + c;

	float p = d * 0.45f;//( 0.3f * 1.5f );
	float s = p * 0.25f;

	if (t < 1)
		return -0.5f * (c * powf(2, 10 * (t -= 1)) * sinf((t * d - s) * (2 * Pi) / p)) + b;
	return c * powf(2, -10 * (t -= 1)) * sinf((t * d - s) * (2 * Pi) / p) * 0.5f + c + b;
}

float Easing::ElasticEaseOutIn(float t, float b, float c, float d) {
	if (t < 0.5f)
		return ElasticEaseOut(t * 2, b, c * 0.5f, d);
	return ElasticEaseIn((t * 2) - 1, b + c * 0.5f, c * 0.5f, d);
}

float Easing::BounceEaseOut(float t, float b, float c, float d) {
	if (t < 0.36363f)//1 * 0.36363f )
		return c * (7.5625f * t * t) + b;
	else if (t < 0.72726f)//2f * 0.36363f )
		return c * (7.5625f * (t -= 0.545445f) * t + 0.75f) + b;
	else if (t < 0.909075f)//2.5f * 0.36363f )
		return c * (7.5625f * (t -= 0.8181675f) * t + 0.9375f) + b;
	else
		return c * (7.5625f * (t -= 0.95452875f) * t + 0.984375f) + b;
}

float Easing::BounceEaseIn(float t, float b, float c, float d) {
	return c - BounceEaseOut(1 - t, 0, c, d) + b;
}

float Easing::BounceEaseInOut(float t, float b, float c, float d) {
	if (t < 0.5f)
		return BounceEaseIn(t * 2, 0, c, d) * 0.5f + b;
	else
		return BounceEaseOut(t * 2 - 1, 0, c, d) * 0.5f + c * 0.5f + b;
}

float Easing::BounceEaseOutIn(float t, float b, float c, float d) {
	if (t < 0.5f)
		return BounceEaseOut(t * 2, b, c * 0.5f, d);
	return BounceEaseIn((t * 2) - 1, b + c * 0.5f, c * 0.5f, d);
}

float Easing::BackEaseOut(float t, float b, float c, float d) {
	return c * ((t = t - 1) * t * (2.70158f * t + 1.70158f) + 1) + b;
}

float Easing::BackEaseIn(float t, float b, float c, float d) {
	return c * t * t * (2.70158f * t - 1.70158f) + b;
}

float Easing::BackEaseInOut(float t, float b, float c, float d) {
	float s = 1.70158f;
	if ((t *= 2) < 1)
		return c * 0.5f * (t * t * (((s *= 1.525f) + 1) * t - s)) + b;
	return c * 0.5f * ((t -= 2) * t * (((s *= 1.525f) + 1) * t + s) + 2) + b;
}

float Easing::BackEaseOutIn(float t, float b, float c, float d) {
	if (t < 0.5f)
		return BackEaseOut(t * 2, b, c * 0.5f, d);
	return BackEaseIn((t * 2) - 1, b + c * 0.5f, c * 0.5f, d);
}