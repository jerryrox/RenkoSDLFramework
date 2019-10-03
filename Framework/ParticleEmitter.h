#pragma once

#ifndef _PARTICLE_EMITTER_
#define _PARTICLE_EMITTER_

#include "Component.h"

#include <functional>
#include <vector>

class UIDisplayer;
class Particle;

class ParticleEmitter :
	public Component
{
public:
	ParticleEmitter();
	~ParticleEmitter() override;

	void Update(float deltaTime) override;

	void Initialize(std::function<Particle*()> createParticle);

	void SetLoop(bool loop);

	// Sets the duration of the particle.
	// If duration is 0, emission is handled in burst mode.
	void SetDuration(float duration);

	// Sets the number of particles to spawn per second.
	// If burst mode, this becomes the number of particles spawned at an instant.
	void SetEmissionRate(float rate);

	// Sets the max number of particles that can be spawned.
	// Default: 100
	void SetMaxEmission(int max);

	// Starts emission.
	void Play();

	// Stops emission.
	void Stop();

	// Clears all currently active particles.
	void Clear();

private:
	bool isEmitting;
	bool isLoop;
	float curTime;
	float duration;
	float curEmitTime;
	float emitRateTime;
	int maxEmission;
	std::function<Particle*()> createParticle;
	std::vector<Particle*> activeParticles;
	std::vector<Particle*> pool;

	Particle* GetNextParticle();
};

#endif