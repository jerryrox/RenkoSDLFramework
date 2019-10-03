#include "MusicController.h"

#include "RenkoFramework.h"
#include "AudioManager.h"
#include "AudioClock.h"
#include "Easing.h"
#include "Debug.h"
#include "game.h"

MusicController::MusicController(RenkoFramework* framework, AudioManager* audioManager) :
	audioManager(0),
	source(0),
	group(0),
	clip(0),
	loopTime(0),
	isLoop(true),
	playedTime(0),
	lastSeekTime(0),
	volume(1),
	fade(1),
	fadeStart(1),
	fadeFactor(1)
{
	this->framework = framework;
	this->audioManager = audioManager;

	audioManager->GetSystem()->createChannelGroup("bgm", &group);
}

MusicController::~MusicController()
{
	framework = 0;
	audioManager = 0;

	if (group != 0)
		group->release();
	group = 0;
}

void MusicController::MountMusic(FMOD::Sound* clip)
{
	if (source != 0 && this->clip != 0)
		source->stop();
	this->clip = clip;
	MountInternal();

	MusicMounted.Invoke();
}

void MusicController::Play() { Play(0.05f); }

void MusicController::Play(float delay)
{
	if (!clock->IsRunning())
		return;

	auto result = source->setPaused(false);

	// Determine the actual value of delay in dsp time.
	unsigned long long dspTime = 0;
	source->getDSPClock(0, &dspTime);
	float frequency = 0;
	source->getFrequency(&frequency);
	dspTime += (unsigned long long)(delay * frequency);

	// Schedule play after delay.
	source->setDelay(dspTime, 0, false);

	// Music play.
	playedTime = framework->GetTimeSinceStart() + delay;
	MusicPlayed.Invoke();
}

void MusicController::Unpause()
{
	if (!clock->IsRunning())
		return;
	source->setPaused(false);
	MusicUnpaused.Invoke();
}

void MusicController::Pause()
{
	if (!clock->IsRunning())
		return;
	source->setPaused(true);
	MusicPaused.Invoke();
}

void MusicController::Stop()
{
	if (!clock->IsRunning())
		return;
	source->setPaused(true);
	source->setPosition(0, FMOD_TIMEUNIT_MS);
	MusicStopped.Invoke();
}

void MusicController::SeekTo(float time)
{
	if (!clock->IsRunning())
		return;

	bool wasPlaying = clock->IsPlaying();
	// Pause audio first
	source->setPaused(true);
	// Change playback position.
	auto result = source->setPosition((unsigned int)time, FMOD_TIMEUNIT_MS);
	// If audio was previously playing, resume it.
	if (wasPlaying)
		source->setPaused(false);

	lastSeekTime = time * 0.001f;
	MusicSeek.Invoke();
}

void MusicController::FadeTo(float start, float target)
{
	SetFade(start);
	FadeTo(target);
}

void MusicController::FadeTo(float volume)
{
	fade = volume;
	StartFade();
}

void MusicController::SetFade(float volume)
{
	source->setVolume(this->volume * volume);
	fadeFactor = 1;
}

void MusicController::SetVolume(float volume)
{
	this->volume = volume;
	if (!IsFading())
		source->setVolume(this->volume * volume);
}

void MusicController::SetClock(AudioClock* clock)
{
	this->clock = clock;
}

float MusicController::GetPlayedTime() { return playedTime; }

float MusicController::GetLastSeekTime() { return lastSeekTime; }

FMOD::Channel* MusicController::GetSource() { return source; }

FMOD::Sound* MusicController::GetClip() { return clip; }

float MusicController::GetDuration()
{
	if (clip == 0)
		return 0;
	unsigned int duration;
	clip->getLength(&duration, FMOD_TIMEUNIT_MS);
	return (float)duration;
}

void MusicController::SetLoopTime(float time) { loopTime = time; }
float MusicController::GetLoopTime() { return loopTime; }

void MusicController::SetLoop(bool loop) { isLoop = loop; }
bool MusicController::IsLoop() { return isLoop; }

bool MusicController::IsPlaying() { return clock->IsPlaying(); }

void MusicController::Update(float deltaTime)
{
	if (source == 0)
		return;

	// Handle fade effect
	if (fadeFactor < 1)
	{
		fadeFactor += deltaTime * 2.5f;
		if (fadeFactor > 1)
			StopFade();
		else
		{
			float target = volume * fade;
			source->setVolume(Easing::Linear(fadeFactor, fadeStart, target-fadeStart, 0));
		}
	}

	// Handle audio end/loop.
	if (clock->IsRunning() && clock->IsPlaying())
	{
		// Get current time in ms.
		float curTime = clock->GetCurrentTime();
		// If reached end time
		if (curTime > GetDuration())
		{
			// Need to re-mount the audio.
			MountInternal();

			// Invoke end
			MusicEnded.Invoke();

			// If loop
			if (isLoop)
			{
				Play();
				FadeTo(0, fade);

				// Seek to loop time
				if (loopTime >= 0 && loopTime < GetDuration())
					SeekTo(loopTime);

				MusicLoop.Invoke();
			}
		}
	}
}

void MusicController::StartFade()
{
	source->getVolume(&fadeStart);
	fadeFactor = 0;
}

void MusicController::StopFade()
{
	source->setVolume(volume * fade);
	fadeFactor = 1;
}

bool MusicController::IsFading() { return fadeFactor < 1; }

void MusicController::MountInternal()
{
	auto result = audioManager->GetSystem()->playSound(clip, group, true, &source);
	source->setChannelGroup(group);
}