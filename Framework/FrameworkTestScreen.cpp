#ifdef _DEBUG

#include "FrameworkTestScreen.h"

#include "FrameworkTestButton.h"
#include "UIAnimatedSprite.h"
#include "MusicController.h"
#include "AudioManager.h"
#include "Transform.h"
#include "UITexture.h"
#include "UISprite.h"
#include "UILabel.h"
#include "Input.h"

FrameworkTestScreen::FrameworkTestScreen()
{
	UIScreen::UIScreen();
}

FrameworkTestScreen::~FrameworkTestScreen()
{
	UIScreen::~UIScreen();
}

void FrameworkTestScreen::Init()
{
	UIScreen::Init();

	parent = gameObject->CreateChild();
	{

	}

	parent->AddChild(button = new FrameworkTestButton());
	{
		
	}

	slicedSprite = parent->CreateChild()->AddComponent(new UISprite());
	{
		slicedSprite->SetSpritename("tests\\round-box");
		slicedSprite->SetPivot(Pivot_TopLeft);
		slicedSprite->SetWrapMode(Sprite_Sliced);
		slicedSprite->SetSize(300, 100);
		slicedSprite->SetColor(128, 255, 128);
		//slicedSprite->GetTransform()->SetLocalPosition(250, 150);
		slicedSprite->SetAlpha(0.5f);
	}
	auto animatedSprite = parent->CreateChild()->AddComponent(new UIAnimatedSprite());
	{
		animatedSprite->SetSpritename("tests\\round-box");
		animatedSprite->GetTransform()->SetLocalPosition(-250, -100);
		animatedSprite->SetAnimationWrap(Wrap_Loop);
		animatedSprite->SetupSlides(2, 2, 4);
		animatedSprite->Play();
	}

	normalLabel = parent->CreateChild()->AddComponent(new UILabel());
	{
		normalLabel->SetText("Music stopped (space to play)");
		normalLabel->SetPivot(Pivot_TopRight);
		normalLabel->GetTransform()->SetLocalPosition(640, -360);
	}
	wrappedLabel = parent->CreateChild()->AddComponent(new UILabel());
	{
		wrappedLabel->SetText("My wrapped text!\nTrololol");
		wrappedLabel->SetPivot(Pivot_BottomLeft);
		wrappedLabel->GetTransform()->SetLocalPosition(-640, 360);
		wrappedLabel->SetFontSize(22);
	}
}

bool FrameworkTestScreen::UpdateInput()
{
	if (Input::IsKeyDown(SDLK_SPACE))
	{
		auto controller = AudioManager::GetInstance()->GetMusicController();
		if (controller->IsPlaying())
		{
			controller->Stop();
			normalLabel->SetText("Music stopped (space to play)");
		}
		else
		{
			controller->Play();
			normalLabel->SetText("Music playing (space to stop)");
		}
	}
	return true;
}

#endif