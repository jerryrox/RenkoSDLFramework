#pragma once

#ifndef _ANIMATOR_
#define _ANIMATOR

#include "Component.h"

#include <map>

class Anime;

class Animator :
	public Component
{
public:
	Animator();
	~Animator() override;

	void Update(float deltaTime) override;

	// Creates a new animation for specified name.
	// May return null if the name is already registered.
	Anime* CreateAnime(std::string name);

	// Returns the animation associated with specified name.
	Anime* GetAnime(std::string name);

	// Removes the animation associated with specified name.
	void RemoveAnime(std::string name, bool shouldDelete = true);

	// Stops all animations.
	void StopAll();

private:
	std::map<std::string, Anime*> animations;
};

#endif