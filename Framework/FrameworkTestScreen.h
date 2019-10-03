#pragma once

#ifdef _DEBUG
#ifndef _FRAMEWORK_TEST_SCREEN_
#define _FRAMEWORK_TEST_SCREEN_

#include "UIScreen.h"

class FrameworkTestButton;
class UIAnimatedSprite;
class UITexture;
class UISprite;
class UILabel;

class FrameworkTestScreen :
	public UIScreen
{
public:
	FrameworkTestScreen();
	~FrameworkTestScreen() override;

	void Init() override;

	bool UpdateInput() override;

private:
	GameObject* parent;

	FrameworkTestButton* button;
	UISprite* slicedSprite;

	UILabel* normalLabel;
	UILabel* wrappedLabel;
};

#endif
#endif