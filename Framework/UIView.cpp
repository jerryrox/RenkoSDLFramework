#include "UIView.h"

#include "InputBlocker.h"
#include "Animator.h"
#include "Easing.h"
#include "Anime.h"

std::string UIView::ShowAniName = "show-ani";
std::string UIView::HideAniName = "hide-ani";

UIView::UIView() :
	UIDisplayer(),
	isShown(false),
	hookedShowAni(false),
	hookedHideAni(false),
	animator(0),
	showAni(0),
	hideAni(0),
	inputBlocker(0)
{
}

UIView::~UIView()
{
	UIDisplayer::~UIDisplayer();
}

void UIView::Init()
{
	UIDisplayer::Init();

	// Views should have an animator by default.
	animator = gameObject->AddComponent(new Animator());
	showAni = animator->CreateAnime(ShowAniName);
	hideAni = animator->CreateAnime(HideAniName);

	// Create input blocker to be shown while animating.
	gameObject->AddChild(inputBlocker = new InputBlocker());
	{
		inputBlocker->SetActive(false);
	}

	// Setup default actions.
	showAni->AddSection(0, 12, EaseType::QuadEaseOut, [&](float progress) {
		SetAlpha((Uint8)Easing::Linear(progress, 0, 255, 0));
	});
	hideAni->AddSection(0, 12, EaseType::QuadEaseOut, [&](float progress) {
		SetAlpha((Uint8)Easing::Linear(progress, 255, -255, 0));
	});
}

void UIView::ShowView()
{
	if (isShown || IsAnimating())
		return;
	isShown = true;

	OnPreShowView();
	// Show view and play animation.
	gameObject->SetActive(true);
	inputBlocker->SetActive(true);
	showAni->PlayAt(0);
}

void UIView::HideView()
{
	if (!isShown || IsAnimating())
		return;
	isShown = false;

	OnPreHideView();
	// Hide view.
	inputBlocker->SetActive(true);
	hideAni->PlayAt(0);
}

void UIView::OnPreShowView()
{
	// Hook on to show animation.
	if (!hookedShowAni)
	{
		hookedShowAni = true;
		showAni->AddEvent(showAni->GetDuration(), [&]() { OnPostShowView(); });
	}

	PreShowed.Invoke();
}

void UIView::OnPostShowView()
{
	inputBlocker->SetActive(false);
}

void UIView::OnPreHideView()
{
	// Hook on to hide animation.
	if (!hookedHideAni)
	{
		hookedHideAni = true;
		hideAni->AddEvent(hideAni->GetDuration(), [&]() { OnPostHideView(); });
	}

	PreHidden.Invoke();
}

void UIView::OnPostHideView()
{
	gameObject->SetActive(false);
	inputBlocker->SetActive(false);
}

inline bool UIView::IsAnimating() { return showAni->IsPlaying() || hideAni->IsPlaying(); }