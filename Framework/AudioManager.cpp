#include "AudioManager.h"

#include "Debug.h"
#include "AudioClips.h"
#include "AudioClock.h"
#include "MusicController.h"

AudioManager* AudioManager::I = 0;

AudioManager::AudioManager(RenkoFramework* framework) :
	musicController(0),
	clock(0),
	clips(0),
	system(0),
	curBgmClip(0),
	curSfxVolume(1),
	curSfxChannel(0)
{
	musicController = new MusicController(framework, this);
	clock = new AudioClock(framework, musicController);
	clips = new AudioClips(this);
}

AudioManager::~AudioManager()
{
	if (musicController != 0)
		delete musicController;
	musicController = 0;

	if (clock != 0)
		delete clock;
	clock = 0;

	if (clips != 0)
		delete clips;
	clips = 0;

	for (int i = 0; i < SfxChannelCount; i++)
		sfxChannels[i]->release();

	if (system != 0)
	{
		system->close();
		system->release();
	}
	system = 0;
}

bool AudioManager::Initialize(RenkoFramework* framework)
{
	if (I != 0)
		return false;
	I = new AudioManager(framework);

	auto result = FMOD::System_Create(&(I->system));
	if (result != FMOD_RESULT::FMOD_OK)
	{
		Debug::Log()->Put("AudioManager::Initialize - Failed to create FMOD system!").Print();
		return false;
	}

	unsigned int version;
	I->system->getVersion(&version);
	if (version < FMOD_VERSION)
	{
		Debug::Log()->Put("AudioManager::Initialize - FMOD version mismatch!").Print();
		return false;
	}

	I->system->init(SfxChannelCount + 1, FMOD_INIT_NORMAL, 0);
	// TODO: uncomment if latency is a concern.
	//I->system->setDSPBufferSize(512, 4);

	for (int i = 0; i < SfxChannelCount; i++)
		I->system->createChannelGroup(std::to_string(i).c_str(), &(I->sfxChannels[i]));
	return true;
}

void AudioManager::Destroy()
{
	if (I != 0)
		delete I;
	I = 0;
}

AudioManager* AudioManager::GetInstance() { return I; }

MusicController* AudioManager::GetMusicController() { return musicController; }

AudioClock* AudioManager::GetClock() { return clock; }

AudioClips* AudioManager::GetClips() { return clips; }

FMOD::System* AudioManager::GetSystem() { return system; }

void AudioManager::PlaySfx(FMOD::Sound* sound)
{
	if (sound == 0)
	{
		Debug::Log()->Print("AudioManager::PlaySfx - The specified sound is null!");
		return;
	}
	// Play audio using the next channel within the pool.
	FMOD::Channel* channel;
	system->playSound(sound, sfxChannels[curSfxChannel], false, &channel);
	channel->setChannelGroup(sfxChannels[curSfxChannel]);
	// Apply volume settings.
	sfxChannels[curSfxChannel]->setVolume(curSfxVolume);

	// Set channel index to next.
	curSfxChannel++;
	if (curSfxChannel >= SfxChannelCount)
		curSfxChannel = 0;
}

void AudioManager::PlaySfx(std::string name)
{
	auto clip = clips->GetClip(name);
	if (clip == 0)
	{
		Debug::Log()->Put("AudioManager::PlaySfx - Could not find clip of name: ").Put(name).Print();
		return;
	}
	PlaySfx(clip);
}

void AudioManager::SetSfxVolume(float volume) { curSfxVolume = volume; }

float AudioManager::GetSfxVolume() { return curSfxVolume; }

void AudioManager::Update()
{
	if (system == 0)
		return;
	system->update();
}