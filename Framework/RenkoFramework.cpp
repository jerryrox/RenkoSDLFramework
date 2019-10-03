#include "RenkoFramework.h"

#include "Debug.h"
#include "Buffer.h"
#include "Input.h"
#include "Atlas.h"
#include "Texture.h"
#include "Easing.h"
#include "UIScreenController.h"
#include "UIOverlayController.h"
#include "AudioManager.h"
#include "AudioClips.h"
#include "MusicController.h"
#include "ConsoleLogger.h"
#include "Random.h"

#include "GameObject.h"

#include <SDL.h>
#include <cstdio>
#include <SDL_keycode.h>

RenkoFramework* RenkoFramework::I = 0;

RenkoFramework::RenkoFramework(float fps) :
	buffer(0),
	input(0),
	rootObject(0),
	isAlive(false),
	fps(0),
	timePerFrame(0),
	maxDeltaTimeScale(5),
	timeScale(1),
	lastTime(0),
	lag(0),
	timeSinceStart(0),
	deltaTime(0)
{
	// Initialize variables
	lastTime = SDL_GetPerformanceCounter();

	// Init dependencies
	Random::Initialize();
	Debug::Initialize(new ConsoleLogger());
	Easing::Initialize();

	if (!Buffer::Initialize())
	{
		Debug::Log()->Put("RenkoFramework - Failed to init Buffer!").Print();
		return;
	}
	buffer = Buffer::GetInstance();

	if (!Atlas::Initialize(buffer->GetRenderer()))
	{
		Debug::Log()->Put("RenkoFramework - Failed to initialize Atlas!").Print();
		return;
	}
	
	if (!Input::Initialize())
	{
		Debug::Log()->Put("RenkoFramework - Failed to initialize Input!").Print();
		return;
	}
	input = Input::GetInstance();

	if (!AudioManager::Initialize(this))
	{
		Debug::Log()->Put("RenkoFramework - Failed to initialize AudioManager!").Print();
		return;
	}

	// Set fps
	SetFps(fps);
}

RenkoFramework::~RenkoFramework()
{
	if (rootObject != 0)
	{
		delete rootObject;
		UIScreenController::Destroy();
		UIOverlayController::Destroy();
	}
	rootObject = 0;

	AudioManager::Destroy();
	Input::Destroy();
	input = 0;
	Atlas::Destroy();
	Buffer::Destroy();
	buffer = 0;
	Easing::Destroy();
	Debug::Destroy();
}

void RenkoFramework::Initialize(float fps)
{
	if (I != 0)
	{
		Debug::Log()->Put("RenkoFramework::Initialize - Already initialized!").Print();
		return;
	}
	I = new RenkoFramework(fps);
}

void RenkoFramework::Destroy()
{
	if (I != 0)
		delete I;
	I = 0;
}

RenkoFramework* RenkoFramework::GetInstance()
{
	if (I == 0)
		Debug::Log()->Put("RenkoFramework::GetInstance - Instance not initialized!").Print();
	return I;
}

void RenkoFramework::Start()
{
	// Some requirements must be met first!
	if (rootObject == 0)
	{
		Debug::Log()->Put("RenkoFramework::Start - rootObject has not been assigned!").Print();
		return;
	}

	// Make the framework go live.
	isAlive = true;

	// Update framework.
	while (ProcessUpdate());
}

void RenkoFramework::Shutdown()
{
	isAlive = false;
}

void RenkoFramework::SetFps(float fps)
{
	this->fps = fps;
	timePerFrame = 1.0f / fps;
}

void RenkoFramework::SetTimescale(float timeScale)
{
	this->timeScale = timeScale;
}

void RenkoFramework::SetRootObject(GameObject* rootObject)
{
	if (this->rootObject != 0)
	{
		Debug::Log()->Put("RenkoFramework::SetRootObject - rootObject as already been set!").Print();
		return;
	}

	this->rootObject = rootObject;
	UIScreenController::Initialize(rootObject);
	UIOverlayController::Initialize(rootObject);
}

float RenkoFramework::GetTimeSinceStart()
{
	return timeSinceStart;
}

float RenkoFramework::GetDeltaTime()
{
	return deltaTime;
}

bool RenkoFramework::ProcessUpdate()
{
	auto audioManager = AudioManager::GetInstance();
	auto musicController = audioManager->GetMusicController();

	if (isAlive)
	{
		Uint64 current = SDL_GetPerformanceCounter();

		// Calculate deltatime
		float dt = (current - lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());
		lastTime = current;

		// Audio should constantly update.
		audioManager->Update();

		// Should update by fps.
		lag += dt;
		if (lag >= timePerFrame)
		{
			// Clamp delta time to avoid spikes in simulation.
			deltaTime = fminf(lag, timePerFrame * maxDeltaTimeScale) * timeScale;

			// Music controller receives a standard update.
			musicController->Update(deltaTime);

			// Update processes for current frame
			timeSinceStart += lag;
			rootObject->PropagateInput();
			rootObject->PropagateUpdate(deltaTime);

			// Draw stuffs
			buffer->Clear();
			rootObject->PropagateRender(buffer);
			buffer->FinalizeRender();

			// Inputs made before logic update gets lost when a next loop cycle occurs
			// without calling Update due to framerate cap.
			// A solution was to move input processing inside this if block but this would mean
			// users may perceive a frame worth of delay, which is similar to Unity's behavior.
			input->Update();

			lag = 0;
		}
	}
	return isAlive;
}