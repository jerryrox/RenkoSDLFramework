#pragma once

#ifndef _AUDIO_MANAGER_
#define _AUDIO_MANAGER_

#include "Events.h"

#include <fmod.hpp>

class MusicController;
class RenkoFramework;
class AudioClock;
class AudioClips;

class AudioManager
{
public:
	static bool Initialize(RenkoFramework* framework);
	static void Destroy();
	static AudioManager* GetInstance();

	Events BgmPlayed;

	MusicController* GetMusicController();

	AudioClock* GetClock();

	AudioClips* GetClips();

	// Returns the audio system instance
	FMOD::System* GetSystem();

	// Plays specified sound as sfx.
	void PlaySfx(FMOD::Sound* sound);

	// Plays the sfx of specified sound name.
	void PlaySfx(std::string name);

	// Sets the volume of the sfx.
	void SetSfxVolume(float volume);

	// Returns the sfx channels' volume.
	float GetSfxVolume();

	// Updates the audio system.
	void Update();

private:
	static const int SfxChannelCount = 32;
	
	static AudioManager* I;

	RenkoFramework* framework;

	MusicController* musicController;
	AudioClock* clock;
	AudioClips* clips;

	FMOD::System* system;
	FMOD::ChannelGroup* sfxChannels[SfxChannelCount];
	FMOD::Sound* curBgmClip;

	float curSfxVolume;
	int curSfxChannel;

	AudioManager(RenkoFramework* framework);
	~AudioManager();
};

#endif