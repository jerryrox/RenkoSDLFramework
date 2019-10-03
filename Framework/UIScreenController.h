#pragma once

#ifndef _UI_SCREEN_CONTROLLER_
#define _UI_SCREEN_CONTROLLER_

#include "UIViewController.h"

class UIScreenController :
	public UIViewController
{
public:
	static void Initialize(GameObject* scene);
	static void Destroy();
	static UIScreenController* GetInstance();

protected:
	UIScreenController(GameObject* scene);

	void OnShowView(UIView* view) override;

private:
	static UIScreenController* I;
};

#endif