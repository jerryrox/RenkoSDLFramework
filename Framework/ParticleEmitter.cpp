#include "ParticleEmitter.h"

#include "Particle.h"
#include "GameObject.h"
#include "RenkoFramework.h"

ParticleEmitter::ParticleEmitter() :
	Component(),
	isEmitting(false),
	isLoop(false),
	curTime(0),
	duration(0),
	curEmitTime(0),
	emitRateTime(0),
	maxEmission(100)
{
	SetEmissionRate(1);
}

ParticleEmitter::~ParticleEmitter()
{
	Component::~Component();

	activeParticles.clear();
	pool.clear();
}

void ParticleEmitter::Update(float deltaTime)
{
	if (isEmitting)
	{
		curEmitTime += duration == 0 ? 1.0f : deltaTime;
		while (curEmitTime >= emitRateTime)
		{
			curEmitTime -= emitRateTime;

			// Only if within max emission number
			if ((int)activeParticles.size() < maxEmission)
			{
				// Setup particle.
				auto particle = GetNextParticle();
				particle->Setup();
				activeParticles.push_back(particle);
			}
		}

		curTime += deltaTime;
		if (curTime >= duration)
		{
			curTime = 0;
			if (!isLoop)
				isEmitting = false;
		}
	}

	for (int i = 0; i < (int)activeParticles.size(); i++)
	{
		auto particle = activeParticles.at(i);
		// Check if particle is dead.
		if (particle->IsDead())
		{
			// Remove from active list
			activeParticles.erase(activeParticles.begin() + i);
			i--;
			// Deactivate particle
			particle->Dispose();
			// Add to pool
			pool.push_back(particle);
		}
	}
}

void ParticleEmitter::Initialize(std::function<Particle*()> createParticle)
{
	this->createParticle = createParticle;
}

void ParticleEmitter::SetLoop(bool loop) { this->isLoop = loop; }

void ParticleEmitter::SetDuration(float duration) { this->duration = duration; }

void ParticleEmitter::SetEmissionRate(float rate) { emitRateTime = 1.0f / fmaxf(0.001f, rate); }

void ParticleEmitter::SetMaxEmission(int max) { maxEmission = max; }

void ParticleEmitter::Play()
{
	isEmitting = true;

	if (duration == 0)
		Update(RenkoFramework::GetInstance()->GetDeltaTime());
}

void ParticleEmitter::Stop()
{
	isEmitting = false;
	curTime = 0;
	curEmitTime = 0;
}

void ParticleEmitter::Clear()
{
	for (int i = (int)activeParticles.size(); i >= 0; i--)
	{
		auto particle = activeParticles.at(i);
		particle->Dispose();
		activeParticles.erase(activeParticles.begin() + i);
		pool.push_back(particle);
	}
}

Particle* ParticleEmitter::GetNextParticle()
{
	Particle* particle = 0;
	int poolSize = (int)pool.size();
	if (poolSize > 0)
	{
		particle = pool.at(poolSize - 1);
		pool.erase(pool.begin() + poolSize - 1);
	}
	else
	{
		gameObject->AddChild(particle = createParticle());
	}
	return particle;
}