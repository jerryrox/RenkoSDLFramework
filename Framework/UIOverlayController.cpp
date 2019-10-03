#include "UIOverlayController.h"

UIOverlayController* UIOverlayController::I = 0;

UIOverlayController::UIOverlayController(GameObject* scene) :
	UIViewController(scene)
{
}

void UIOverlayController::Initialize(GameObject* scene)
{
	if (I != 0)
		return;
	I = new UIOverlayController(scene);
}

void UIOverlayController::Destroy()
{
	if (I != 0)
		delete I;
	I = 0;
}

UIOverlayController* UIOverlayController::GetInstance() { return I; }