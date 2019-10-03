#pragma once

#ifndef _SCENE_
#define _SCENE_

#include "GameObject.h"

class Scene :
	public GameObject
{
public:
	Scene();
	~Scene() override;

	void Init() override;

	void Update(float deltaTime) override;

private:
	void AdjustScreen();
};

#endif