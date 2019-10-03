#pragma once

#ifndef _ANIME_SECTION_
#define _ANIME_SECTION_

#include "Easing.h"

#include <functional>

class AnimeSection
{
public:
	AnimeSection(float frameTime, int from, int to, EaseType easeType, std::function<void(float)> action);
	~AnimeSection();

	int GetFrom();
	int GetTo();
	int GetDuration();

	void SeekState(int frame);
	void UpdateState(int frame);

protected:
	bool isActive;
	int curFrame;
	int lastFrame;

	float frameTime;
	int duration;
	int from;
	int to;
	EaseType easeType;
	std::function<void(float)> action;

	virtual void ActivateState();

private:
	float GetProgress();
	bool ShouldBeActive();
};

#endif