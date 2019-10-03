#pragma once

#ifndef _RENKO_FRAMEWORK_
#define _RENKO_FRAMEWORK_

class GameObject;
class Buffer;
class Input;

class RenkoFramework
{
public:
	static void Initialize(float fps);
	static void Destroy();
	static RenkoFramework* GetInstance();

	// Starts the framework processing.
	void Start();

	// Stops the framework processing.
	void Shutdown();

	// Sets the number of frames to be updated per second.
	void SetFps(float fps);

	// Sets the multiplier factor applied to deltaTime to simulate fast/slow motion on the
	// same framerate.
	void SetTimescale(float timeScale);

	// Sets the root GameObject which holds all child objects.
	void SetRootObject(GameObject* rootObject);

	// Returns the amount of time in seconds since the game has started.
	float GetTimeSinceStart();

	// Returns the last deltatime calculated.
	float GetDeltaTime();

private:
	static RenkoFramework* I;

	Buffer* buffer;
	Input* input;
	GameObject* rootObject;

	bool isAlive;

	float fps;
	float timePerFrame;
	float maxDeltaTimeScale;

	float timeScale;

	__int64 lastTime;
	float lag;
	float timeSinceStart;
	float deltaTime;

	RenkoFramework(float fps);
	~RenkoFramework();

	bool ProcessUpdate();
};

#endif