#pragma once

#ifndef _AUDIO_CLOCK_
#define _AUDIO_CLOCK_

class MusicController;
class RenkoFramework;

class AudioClock
{
public:
	AudioClock(RenkoFramework* framework, MusicController* musicController);
	~AudioClock();

	bool IsRunning();
	bool IsPlaying();
	bool IsPaused();
	bool IsStopped();
	float GetStartTime();
	void SetOffset(float offset);
	float GetOffset();
	float GetCurrentTime();

private:
	RenkoFramework* framework;

	MusicController* musicController;
	// The realtime at which the clock started.
	float startTime;
	// The realtime at which the clock paused.
	float pauseTime;
	// Whether the clock is running.
	bool isRunning;
	// Whether the audio is playing.
	bool isPlaying;
	// Whether the audio is paused.
	bool isPaused;
	// Amount of offset to apply on clock.
	float offset;
};

#endif