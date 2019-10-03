#include "Anime.h"
#include "AnimeSection.h"
#include "AnimeEventSection.h"

#include "Debug.h"

#include <algorithm>

Anime::Anime(int fps) :
	frameTime(0),
	currentTime(0),
	duration(0),
	currentFrame(0),
	lastFrame(0),
	isPlaying(false),
	wrapMode(Wrap_None),
	stopMode(Stop_Reset)
{
	frameTime = 1.0f / fps;
}

Anime::~Anime()
{
	for (int i = 0; i < (int)sections.size(); i++)
		delete sections.at(i);
	sections.clear();
}

int Anime::GetDuration() { return duration; }

float Anime::GetTimeDuration() { return duration * frameTime; }

int Anime::GetCurrentFrame() { return lastFrame; }

bool Anime::IsPlaying() { return isPlaying; }

void Anime::AddSection(int from, int to, std::function<void(float)> action)
{
	AddSection(from, to, Linear, action);
}

void Anime::AddSection(int from, int to, EaseType easeType, std::function<void(float)> action)
{
	if (from < 0 || to < 0 || to <= from)
		return;

	AddSection(new AnimeSection(frameTime, from, to, easeType, action));
	if (to > duration)
		duration = to;
}

void Anime::AddEvent(int frame, std::function<void(void)> action)
{
	if (frame < 0)
		return;

	AddSection(new AnimeEventSection(this, frame, action));
	if (frame > duration)
		duration = frame;
}

void Anime::SetWrapMode(AnimationWrap mode) { wrapMode = mode; }

void Anime::SetStopMode(AnimationStop mode) { stopMode = mode; }

void Anime::Play()
{
	if (duration > 0 && !isPlaying)
	{
		isPlaying = true;
		// Refresh state
		SeekState(OverrideFrame(currentFrame));
	}
}

void Anime::PlayAt(int frame)
{
	SeekTo(frame);
	Play();
}

void Anime::Pause()
{
	if (duration > 0 && isPlaying)
	{
		isPlaying = false;
		// Refresh state
		UpdateState(OverrideFrame(currentFrame));
	}
}

void Anime::Stop()
{
	if (duration > 0)
	{
		isPlaying = false;

		// Stop wrap
		switch (stopMode)
		{
		case Stop_None:
			SeekState(OverrideFrame(currentFrame));
			break;
		case Stop_Reset:
			SeekState(OverrideFrame(0));
			break;
		case Stop_End:
			SeekState(OverrideFrame(duration));
			break;
		}
	}
}

void Anime::SeekTo(int frame)
{
	SeekState(OverrideFrame(frame));
}

void Anime::Update(float deltaTime)
{
	if (!isPlaying)
		return;

	// Perform progression
	currentTime += deltaTime;
	currentFrame = (int)(currentTime / frameTime);

	// If frame update
	if (currentFrame != lastFrame)
	{
		// End of frame
		if (currentFrame >= duration)
		{
			// Flush events
			UpdateState(duration);
			// Wrap animation
			switch (wrapMode)
			{
			case Wrap_None:
				Pause();
				return;
			case Wrap_Reset:
				Pause();
				SeekTo(0);
				return;
			case Wrap_Loop:
				SeekState(0);
				lastFrame = 0;
				float timeDuration = GetTimeDuration();
				while (currentTime > timeDuration)
					currentTime -= timeDuration;
				currentFrame %= duration;
				break;
			}
		}

		// Store frame
		lastFrame = currentFrame;

		// Update state
		UpdateState(currentFrame);
	}
}

int Anime::OverrideFrame(int frame)
{
	if (frame < 0) frame = 0;
	else if (frame > duration) frame = duration;

	lastFrame = currentFrame = frame;
	currentTime = frame * frameTime;
	return frame;
}

void Anime::SeekState(int frame)
{
	for (int i = 0; i < (int)sections.size(); i++)
		sections.at(i)->SeekState(frame);
}

void Anime::UpdateState(int frame)
{
	for (int i = 0; i < (int)sections.size(); i++)
		sections.at(i)->UpdateState(frame);
}

bool Anime::CompareSection(AnimeSection* x, AnimeSection* y)
{
	return x->GetFrom() < y->GetFrom();
}

inline void Anime::AddSection(AnimeSection* section)
{
	//std::sort(sections.begin(), sections.end());
	sections.push_back(section);
}