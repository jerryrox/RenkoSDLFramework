#include "UIViewController.h"

#include "UIView.h"

UIViewController::UIViewController(GameObject* scene)
{
	this->scene = scene;
}

UIViewController::~UIViewController()
{
	scene = 0;
	views.clear();
}

void UIViewController::HideView(UIView* view)
{
	view->HideView();
	OnHideView(view);
}

void UIViewController::OnShowView(UIView* view) {}

void UIViewController::OnHideView(UIView* view) {}