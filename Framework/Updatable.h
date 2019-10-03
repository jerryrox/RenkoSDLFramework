#pragma once

#ifndef _UPDATABLE_
#define _UPDATABLE_

class Buffer;

class Updatable
{
public:
	Updatable();
	virtual ~Updatable();

	// Handles initialization of the updatable.
	virtual void Init();

	// Sets the enable state of the object.
	virtual void SetEnable(bool enabled);

	// Returns whether the object is enabled.
	bool IsEnabled();

	// Flags this updatable for destruction on next frame.
	virtual void Destroy();

	// Whether the updatable should be destroyed this frame.
	bool IsDestroying();

	// Updates the behavior with specified delta time.
	virtual void Update(float deltaTime) = 0;

	// Updates input logics.
	// Returns whether input will further propagate to lower-depth objects.
	virtual bool UpdateInput();

	// Event called when the behavior is about to be destroyed.
	virtual void OnDestroy() = 0;

protected:
	bool isEnabled;
	bool isDestroying;

	// Event called when this updatable has been enabled.
	virtual void OnEnable() = 0;

	// Event called when the updatable has been disabled.
	virtual void OnDisable() = 0;
};

#endif