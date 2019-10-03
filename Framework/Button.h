#pragma once

#ifndef _BUTTON_
#define _BUTTON_

#include "CursorInteractible.h"

class Animator;
class Anime;

class Button :
	public CursorInteractible
{
public:
	Button();
	~Button() override;

	void Init() override;

	void OnCursorOver() override;
	void OnCursorOut() override;
	void OnCursorPress() override;
	void OnCursorRelease() override;
	void OnCursorClick() override;

	// Sets the name of sound to be played on cursor over event.
	void SetHitSoundName(std::string name);

	// Sets the name of the sound to be played on cursor click event.
	void SetClickSoundName(std::string name);

protected:
	Animator* animator;
	Anime* cursorOverAni;
	Anime* cursorOutAni;
	Anime* cursorPressAni;
	Anime* cursorReleaseAni;

	std::string hitSoundName;
	std::string clickSoundName;
};

#endif