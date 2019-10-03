#pragma once

#ifndef _INPUT_BLOCKER_
#define _INPUT_BLOCKER_

#include "GameObject.h"

// A type of GameObject which blocks inputs propagating to adjacent children objects.
class InputBlocker :
	public GameObject
{
public:
	InputBlocker();
	~InputBlocker() override;

	void Init() override;

	bool UpdateInput() override;
};

#endif