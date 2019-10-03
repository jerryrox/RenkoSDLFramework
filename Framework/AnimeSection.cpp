#include "AnimeSection.h"

AnimeSection::AnimeSection(float frameTime, int from, int to, EaseType easeType, std::function<void(float)> action) :
	isActive(false),
	curFrame(0),
	lastFrame(0)
{
	this->frameTime = frameTime;
	this->duration = to - from;
	this->from = from;
	this->to = to;
	this->easeType = easeType;
	this->action = action;
}

AnimeSection::~AnimeSection()
{
	isActive = false;
	action = 0;
}

int AnimeSection::GetFrom() { return from; }

int AnimeSection::GetTo() { return to; }

int AnimeSection::GetDuration() { return duration; }

void AnimeSection::SeekState(int frame)
{
	lastFrame = curFrame = frame - 1;
	isActive = true;
	UpdateState(frame);
}

void AnimeSection::UpdateState(int frame)
{
	lastFrame = curFrame;
	curFrame = frame;

	if (frame < from || (frame > to && lastFrame >= to))
		return;

	if (!isActive)
		return;

	ActivateState();
	isActive = ShouldBeActive();
}

void AnimeSection::ActivateState()
{
	action(Easing::Ease(easeType, GetProgress(), 0, 1, duration * frameTime));
}

float AnimeSection::GetProgress()
{
	float progress = ((float)curFrame - (float)from) / ((float)to - (float)from);
	if (progress < 0)
		return 0;
	else if (progress > 1)
		return 1;
	return progress;
}

bool AnimeSection::ShouldBeActive() { return curFrame >= from && curFrame <= to; }