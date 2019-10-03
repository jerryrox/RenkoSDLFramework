#include "Particle.h"

#include "Transform.h"

Particle::Particle() :
	GameObject(),
	curTime(0),
	duration(0)
{
}

Particle::~Particle()
{
	GameObject::~GameObject();
}

void Particle::Init()
{
	GameObject::Init();

	lastPosX = posX = 0;
	lastPosY = posY = 0;
	lastScaleX = scaleX = 1;
	lastScaleY = scaleY = 1;
}

void Particle::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	curTime += deltaTime;
	if (curTime > duration)
		curTime = duration;

	if (duration > 0)
		progress = curTime / duration;

	if(posX != lastPosX || posY != lastPosY)
		transform->SetLocalPosition(lastPosX = posX, lastPosY = posY);

	if (scaleX != lastScaleX || scaleY != lastScaleY)
		transform->SetLocalScale(lastScaleX = scaleX, lastScaleY = scaleY);
}

void Particle::Setup()
{
	SetActive(true);
	curTime = 0;
	progress = 0;
}

void Particle::Dispose()
{
	SetActive(false);
}

bool Particle::IsDead() { return curTime >= duration; }