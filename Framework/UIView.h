#pragma once

#ifndef _UI_VIEW_
#define _UI_VIEW_

#include "UIDisplayer.h"

#include "Events.h"

// Add these so I don't have to type these bs all the time
#include "UIScreenController.h"
#include "UIOverlayController.h"
#include "UIViewController.h"

class InputBlocker;
class Animator;
class Anime;

class UIView :
	public UIDisplayer
{
public:
	static std::string ShowAniName;
	static std::string HideAniName;

	Events PreShowed;
	Events PreHidden;

	UIView();
	~UIView() override;

	void Init() override;

	// Shows the view with animation, if applicable.
	void ShowView();

	// Hides the view with animation, if applicable.
	void HideView();

protected:
	bool isShown;
	bool hookedShowAni;
	bool hookedHideAni;
	Animator* animator;
	// Animation to be played on showing the view.
	Anime* showAni;
	// Animation to be played on hiding the view.
	Anime* hideAni;

	// Event called before actually showing the view.
	virtual void OnPreShowView();
	// Event called when show animation is finished.
	virtual void OnPostShowView();
	// Event called before actually hiding the view.
	virtual void OnPreHideView();
	// Event called when hide animation is finished.
	virtual void OnPostHideView();

private:
	InputBlocker* inputBlocker;

	// Returns whether a show/hide ani is playing.
	bool IsAnimating();
};

#endif