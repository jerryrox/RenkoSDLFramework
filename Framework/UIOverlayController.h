#pragma once

#ifndef _UI_OVERLAY_CONTROLLER_	
#define _UI_OVERLAY_CONTROLLER_	

#include "UIViewController.h"

class UIOverlayController :
	public UIViewController
{
public:
	static void Initialize(GameObject* scene);
	static void Destroy();
	static UIOverlayController* GetInstance();

protected:
	UIOverlayController(GameObject* scene);

private:
	static UIOverlayController* I;
};

#endif