#pragma once

#ifndef _MUSIC_CONTROLLER_
#define _MUSIC_CONTROLLER_

#include "Events.h"
#include <fmod.hpp>

class AudioClock;
class AudioManager;
class RenkoFramework;

class MusicController
{
public:
	Events MusicMounted;
	Events MusicPlayed;
	Events MusicUnpaused;
	Events MusicPaused;
	Events MusicStopped;
	Events MusicSeek;
	Events MusicEnded;
	Events MusicLoop;

	MusicController(RenkoFramework* framework, AudioManager* audioManager);
	~MusicController();

	// Sets the audio clip to be played by this controller.
	void MountMusic(FMOD::Sound* clip);

	// Plays music with default delay.
	void Play();

	// Plays music with specified delay in seconds.
	void Play(float delay);

	// Unpauses music playback.
	void Unpause();

	// Pauses music playback.
	void Pause();

	// Stops music playback.
	void Stop();

	// Seeks time to specified time in ms.
	void SeekTo(float time);

	// Fades from specified start to target volumes.
	void FadeTo(float start, float target);

	// Fades to specified fade factor.
	void FadeTo(float volume);

	// Instantly sets fade amount on the music.
	void SetFade(float volume);

	// Sets the volume of the music.
	void SetVolume(float volume);

	// Sets the clock instance which the music actions will be driven based on.
	void SetClock(AudioClock* clock);

	float GetPlayedTime();

	float GetLastSeekTime();
	
	FMOD::Channel* GetSource();

	FMOD::Sound* GetClip();

	// Returns the clip duration in ms.
	float GetDuration();

	// Sets the loop time in ms.
	void SetLoopTime(float time);
	float GetLoopTime();

	// Sets whether the audio should loop.
	void SetLoop(bool loop);
	bool IsLoop();

	// Whether the music is playing.
	bool IsPlaying();

	// Updates music controller logic.
	void Update(float deltaTime);

private:
	RenkoFramework* framework; 

	AudioClock* clock;

	AudioManager* audioManager;
	FMOD::Channel* source;
	FMOD::ChannelGroup* group;
	FMOD::Sound* clip;
	float loopTime;
	bool isLoop;

	// The time when the music was played.
	float playedTime;
	// The time when last seek occurred.
	float lastSeekTime;

	float volume;
	float fade;
	float fadeStart;
	float fadeFactor;

	// Sets variables ready for fading effect.
	void StartFade();

	// Sets variables ready for fade stop.
	void StopFade();

	// Whether fade effect is going on.
	bool IsFading();

	void MountInternal();
};

#endif