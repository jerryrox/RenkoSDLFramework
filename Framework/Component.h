#pragma once

#ifndef _COMPONENT_
#define _COMPONENT_

#include "Updatable.h"

class GameObject;
class Transform;
class Buffer;

class Component :
	public Updatable
{
public:
	Component();
	~Component() override;

	// Returns the game object this component is attached to.
	GameObject* GetGameObject();

	// Convenience function for accessing the owner object's transform.
	Transform* GetTransform();

	// Assigns the GameObject instance to which the component is attached.
	void AssignObject(GameObject* object);
	
	// Handles rendering routine of the component.
	// Does nothing by default.
	virtual void Render(Buffer* buffer);

	// Event called when the owner object has become active in hierarchy.
	void OnActive();

	// Event called when the object object has become inactive in hierarchy.
	void OnInactive();

	void Update(float deltaTime) override;

	void OnDestroy() override;

protected:
	// The GameObject instance which this component is attached to.
	GameObject* gameObject;

	void OnEnable() override;

	void OnDisable() override;

private:
	bool shouldDestroy;
};

#endif