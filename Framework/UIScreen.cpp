#include "UIScreen.h"

#include "Anime.h"
#include "Easing.h"
#include "Transform.h"

UIScreen::UIScreen() :
	UIView()
{
}

UIScreen::~UIScreen()
{
	UIView::~UIView();
}

void UIScreen::Init()
{
	UIView::Init();

	if (UseDefaultAnimation())
	{
		showAni->AddSection(0, 12, EaseType::QuadEaseOut, [&](float progress) {
			float scale = Easing::Linear(progress, 1.15f, -0.15f, 0);
			GetTransform()->SetLocalScale(
				scale,
				scale
			);
		});
		hideAni->AddSection(0, 12, EaseType::QuadEaseOut, [&](float progress) {
			float scale = Easing::Linear(progress, 1.0f, 0.15f, 0);
			GetTransform()->SetLocalScale(
				scale,
				scale
			);
		});
	}
}