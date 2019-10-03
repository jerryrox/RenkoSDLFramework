#ifdef _DEBUG

#include "FrameworkTestButton.h"

#include "Transform.h"
#include "UISprite.h"
#include "UILabel.h"
#include "Easing.h"
#include "Random.h"
#include "Anime.h"

FrameworkTestButton::FrameworkTestButton() :
	Button()
{
}

FrameworkTestButton::~FrameworkTestButton()
{
	Button::~Button();
}

void FrameworkTestButton::Init()
{
	Button::Init();

	hitSoundName = "tests\\hit";
	clickSoundName = "tests\\click";

	bg = CreateChild()->AddComponent(new UISprite());
	{
		bg->GetGameObject()->SetDepth(-1);
		bg->SetSpritename("tests\\button");
		bg->ResetSize();
		bg->SetAlpha(0.5f);

		// Set cursor interactible area target.
		SetTarget(bg);
	}
	label = CreateChild()->AddComponent(new UILabel());
	{
		label->SetText("Button!");
	}

	// Setup animations
	cursorOverAni->AddSection(0, 9, [&](float progress) {
		bg->SetAlpha(Easing::QuadEaseOut(progress, 0.5f, 0.5f, 0));
	});
	cursorOutAni->AddSection(0, 9, [&](float progress) {
		bg->SetAlpha(Easing::QuadEaseIn(progress, 1.0f, -0.5f, 0));
	});
	cursorPressAni->AddSection(0, 9, [&](float progress) {
		float scale = Easing::BackEaseOut(progress, 1, 0.15f, 0.15f);
		GetTransform()->SetLocalScale(scale, scale);
	});
	cursorReleaseAni->AddSection(0, 9, [&](float progress) {
		float scale = Easing::QuadEaseIn(progress, 1.15f, -0.15f, 0);
		GetTransform()->SetLocalScale(scale, scale);
	});

	// Set click callback
	Clicked += [&]() {
		label->SetColor(
			(Uint8)Random::Range(128, 255),
			(Uint8)Random::Range(128, 255),
			(Uint8)Random::Range(128, 255)
		);
	};
}

#endif