#include "Button.h"

#include "AudioManager.h"
#include "Animator.h"
#include "Anime.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::Init()
{
	CursorInteractible::Init();

	animator = AddComponent(new Animator());
	cursorOverAni = animator->CreateAnime("cursoroverani");
	cursorOutAni = animator->CreateAnime("cursoroutani");
	cursorPressAni = animator->CreateAnime("cursorpressani");
	cursorReleaseAni = animator->CreateAnime("cursorreleaseani");
}

void Button::OnCursorOver()
{
	CursorInteractible::OnCursorOver();
	cursorOutAni->Stop();
	cursorOverAni->PlayAt(0);

	AudioManager::GetInstance()->PlaySfx(hitSoundName);
}

void Button::OnCursorOut()
{
	CursorInteractible::OnCursorOut();
	cursorOverAni->Stop();
	cursorOutAni->PlayAt(0);
}

void Button::OnCursorPress()
{
	CursorInteractible::OnCursorPress();
	cursorReleaseAni->Stop();
	cursorPressAni->PlayAt(0);
}

void Button::OnCursorRelease()
{
	CursorInteractible::OnCursorRelease();
	cursorPressAni->Stop();
	cursorReleaseAni->PlayAt(0);
}

void Button::OnCursorClick()
{
	CursorInteractible::OnCursorClick();

	AudioManager::GetInstance()->PlaySfx(clickSoundName);
}

void Button::SetHitSoundName(std::string name) { hitSoundName = name; }

void Button::SetClickSoundName(std::string name) { clickSoundName = name; }