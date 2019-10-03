#include "UIScreenController.h"

UIScreenController* UIScreenController::I = 0;

UIScreenController::UIScreenController(GameObject* scene) :
	UIViewController(scene)
{
}

void UIScreenController::Initialize(GameObject* scene)
{
	if (I != 0)
		return;
	I = new UIScreenController(scene);
}

void UIScreenController::Destroy()
{
	if (I != 0)
		delete I;
	I = 0;
}

UIScreenController* UIScreenController::GetInstance() { return I; }

void UIScreenController::OnShowView(UIView* view)
{
	// There should be only one active screen at a time.
	for (int i = 0; i < (int)views.size(); i++)
	{
		UIView* v = views.at(i);
		if (v != view)
			HideView(v);
	}
}