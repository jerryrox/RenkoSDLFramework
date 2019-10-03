#pragma once

#ifdef _DEBUG
#ifndef _FRAMEWORK_TEST_BUTTON_
#define _FRAMEWORK_TEST_BUTTON_

#include "Button.h"

class UISprite;
class UILabel;

class FrameworkTestButton :
	public Button
{
public:
	FrameworkTestButton();
	~FrameworkTestButton() override;

	void Init() override;

private:
	UISprite* bg;
	UILabel* label;
};

#endif
#endif