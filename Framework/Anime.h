#pragma once

#ifndef _ANIME_
#define _ANIME_

#include <vector>
#include <functional>
#include "EaseType.h"
#include "AnimationStop.h"
#include "AnimationWrap.h"

class AnimeSection;

class Anime
{
public:
	Anime(int fps = 60);
	~Anime();

	int GetDuration();
	float GetTimeDuration();
	int GetCurrentFrame();
	bool IsPlaying();

	void AddSection(int from, int to, std::function<void(float)> action);
	void AddSection(int from, int to, EaseType easeType, std::function<void(float)> action);
	void AddEvent(int frame, std::function<void(void)> action);

	void SetWrapMode(AnimationWrap mode);
	void SetStopMode(AnimationStop mode);

	void Play();
	void PlayAt(int frame);
	void Pause();
	void Stop();
	void SeekTo(int frame);

	void Update(float deltaTime);

private:
	float frameTime;
	float currentTime;
	int duration;
	int currentFrame;
	int lastFrame;
	bool isPlaying;
	AnimationWrap wrapMode;
	AnimationStop stopMode;
	std::vector<AnimeSection*> sections;

	int OverrideFrame(int frame);
	void SeekState(int frame);
	void UpdateState(int frame);
	bool CompareSection(AnimeSection* x, AnimeSection* y);

	void AddSection(AnimeSection* section);
};

#endif