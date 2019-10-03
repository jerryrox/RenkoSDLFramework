#pragma once

#ifndef _PARTICLE_
#define _PARTICLE_

#include "GameObject.h"

class Particle :
	public GameObject
{
public:
	Particle();
	~Particle();

	void Init() override;

	void Update(float deltaTime) override;

	virtual void Setup();

	virtual void Dispose();

	virtual bool IsDead();

protected:
	float curTime;
	float duration;
	float progress;

	float posX;
	float posY;
	float scaleX;
	float scaleY;

private:
	float lastPosX;
	float lastPosY;
	float lastScaleX;
	float lastScaleY;
};

#endif