#include "AudioClock.h"

#include "MusicController.h"
#include "RenkoFramework.h"
#include "game.h"

AudioClock::AudioClock(RenkoFramework* framework, MusicController* musicController) :
	musicController(0),
	startTime(0),
	pauseTime(0),
	isRunning(false),
	isPlaying(false),
	isPaused(false),
	offset(0)
{
	this->framework = framework;
	this->musicController = musicController;
	musicController->SetClock(this);

	musicController->MusicMounted += [&]() {
		isRunning = this->musicController->GetClip() != 0;
	};
	musicController->MusicPlayed += [&]() {
		isPlaying = true;
		startTime = this->musicController->GetPlayedTime();
	};
	musicController->MusicUnpaused += [&]() {
		if (isPlaying || !isPaused)
			return;
		isPlaying = true;
		isPaused = false;
		startTime += this->framework->GetTimeSinceStart() - pauseTime;
	};
	musicController->MusicPaused += [&]() {
		if (!isPlaying || isPaused)
			return;
		isPlaying = false;
		isPaused = true;
		pauseTime = this->framework->GetTimeSinceStart();
	};
	musicController->MusicStopped += [&]() {
		isPlaying = false;
		isPaused = false;
		startTime = pauseTime = this->framework->GetTimeSinceStart();
	};
	musicController->MusicSeek += [&]() {
		float timeSinceStartup = this->framework->GetTimeSinceStart();
		startTime = timeSinceStartup - this->musicController->GetLastSeekTime();
	};
}

AudioClock::~AudioClock()
{
	framework = 0;
	musicController = 0;
}

bool AudioClock::IsRunning() { return isRunning; }
bool AudioClock::IsPlaying() { return isPlaying; }
bool AudioClock::IsPaused() { return isPaused; }
bool AudioClock::IsStopped() { return !isPlaying && !isPaused; }
float AudioClock::GetStartTime() { return startTime * 1000; }
void AudioClock::SetOffset(float offset) { this->offset = offset; }
float AudioClock::GetOffset() { return offset; }
float AudioClock::GetCurrentTime()
{
	float curStartupTime = framework->GetTimeSinceStart();
	float time = curStartupTime - startTime;
	if (!isPlaying)
		time -= curStartupTime - pauseTime;
	return (time + offset) * 1000.0f;
}