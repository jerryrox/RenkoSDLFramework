#include "AudioClips.h"

#include "AudioManager.h"
#include "Debug.h"

AudioClips::AudioClips(AudioManager* audioManager) :
	audioManager(0)
{
	this->audioManager = audioManager;
}

AudioClips::~AudioClips()
{
	std::map<std::string, FMOD::Sound*>::iterator i;
	for (i = clips.begin(); i != clips.end(); i++)
		i->second->release();
	clips.clear();
}

void AudioClips::LoadClip(std::string name, std::string extension, bool isStream)
{
	// If existing name, return.
	if (clips.find(name) != clips.end())
	{
		Debug::Log()->Put("AudioClips::LoadClip - Name already exists: ").Put(name).Print();
		return;
	}
	// Get actual path
	std::string path("assets\\audio\\");
	path.append(name).append(extension);

	// Load clip
	FMOD::Sound* clip = 0;
	auto result = (
		isStream ?
		audioManager->GetSystem()->createStream(path.c_str(), FMOD_CREATECOMPRESSEDSAMPLE | FMOD_2D, 0, &clip) :
		audioManager->GetSystem()->createSound(path.c_str(), FMOD_DEFAULT, 0, &clip)
	);
	if(result == FMOD_RESULT::FMOD_OK)
		clips.emplace(name, clip);
	else
		Debug::Log()->Put("AudioClips::LoadClip - Failed to create sound: ").Put(path).Put(", Reason: ").Put(result).Print();
}

FMOD::Sound* AudioClips::LoadExternalClip(std::string path, bool isStream)
{
	// Load clip
	FMOD::Sound* clip = 0;
	auto result = (
		isStream ?
		audioManager->GetSystem()->createStream(path.c_str(), FMOD_CREATECOMPRESSEDSAMPLE | FMOD_2D, 0, &clip) :
		audioManager->GetSystem()->createSound(path.c_str(), FMOD_DEFAULT, 0, &clip)
	);
	if (result == FMOD_RESULT::FMOD_OK)
		return clip;
	else
		Debug::Log()->Put("AudioClips::LoadExternalClip - Failed to create sound: ").Put(path).Put(isStream ? ", as stream" : ", as sound").Put(", Reason: ").Put(result).Print();
	return 0;
}

FMOD::Sound* AudioClips::GetClip(std::string name)
{
	if (clips.find(name) != clips.end())
		return clips[name];
	return 0;
}