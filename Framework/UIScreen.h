#pragma once

#ifndef _UI_SCREEN_
#define _UI_SCREEN_

#include "UIView.h"

class UIScreen :
	public UIView
{
public:
	UIScreen();
	~UIScreen() override;

	void Init() override;

protected:
	// Whether default animation should be used.
	// Default: true.
	virtual bool UseDefaultAnimation() { return true; }
};

#endif