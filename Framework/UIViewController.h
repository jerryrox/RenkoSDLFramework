#pragma once

#ifndef _UI_VIEW_CONTROLLER_
#define _UI_VIEW_CONTROLLER_

#include "Debug.h"

#include <vector>

class UIView;
class GameObject;

class UIViewController
{
public:
	// Shows the view of specified type and returns it.
	template <class T>
	T* ShowView()
	{
		T* t = 0;
		for (int i = 0; i < (int)views.size(); i++)
		{
			t = dynamic_cast<T*>(views.at(i));
			if (t != 0)
				break;
		}
		if (t == 0)
		{
			t = new T();
			if (dynamic_cast<UIView*>(t) == 0)
			{
				Debug::Log()->Print("UIViewController::ShowView - Invalid argument T was passed!");
				delete t;
				return 0;
			}
			views.push_back(t);
			scene->AddChild(new GameObject(std::string(typeid(T).name())))->AddComponent(t);
		}
		UIView* view = t;
		view->ShowView();
		OnShowView(view);
		return t;
	}

	// Hides the view of specified type.
	template <class T>
	void HideView()
	{
		for (int i = 0; i < (int)views.size(); i++)
		{
			auto view = views.at(i);
			T* t = dynamic_cast<T*>(view);
			if (t != 0)
			{
				view->HideView();
				OnHideView(view);
				return;
			}
		}
	}

	template <class T>
	T* GetView()
	{
		for (int i = 0; i < (int)views.size(); i++)
		{
			T* t = dynamic_cast<T*>(views.at(i));
			if (t != 0)
				return t;
		}
		return 0;
	}

	// Hides the specified view.
	void HideView(UIView* view);

protected:
	GameObject* scene;
	//std::vector<std::unique_ptr<UIView>> views;
	std::vector<UIView*> views;

	UIViewController(GameObject* scene);
	virtual ~UIViewController();

	// Event called when the specified view has been shown.
	virtual void OnShowView(UIView* view);

	// Event called when the specified view has been hidden.
	virtual void OnHideView(UIView* view);
};

#endif