#pragma once

#ifndef _AUDIO_CLIPS_
#define _AUDIO_CLIPS_

#include <fmod.hpp>
#include <string>
#include <map>
#include <vector>

class AudioManager;

class AudioClips
{
public:
	AudioClips(AudioManager* audioManager);
	~AudioClips();

	// Loads the default audio clip included in game resources.
	void LoadClip(std::string name, std::string extension, bool isStream);
	
	// Loads an audio clip with explicit location.
	// Clip loaded via this method should be released manually.
	FMOD::Sound* LoadExternalClip(std::string path, bool isStream);

	// Returns the sound of specified name.
	FMOD::Sound* GetClip(std::string name);

private:
	AudioManager* audioManager;
	std::map<std::string, FMOD::Sound*> clips;

	// Interhalls handles loading of clip.
	FMOD_RESULT LoadClip(std::string path, FMOD::Sound* clip, bool isStream);
};

#endif