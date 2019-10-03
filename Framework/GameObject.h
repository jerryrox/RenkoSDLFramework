#pragma once

#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include "Updatable.h"

#include "Debug.h"

#include "Vector2.h"
#include <vector>
#include <typeinfo>

class Buffer;
class Component;
class Transform;

class GameObject :
	public Updatable
{
public:
	GameObject();
	GameObject(std::string name);
	~GameObject() override;

	void Init() override;

	// Returns the name of the object.
	std::string GetName();

	// Returns the parent object.
	GameObject* GetParent();

	// Sets the processing depth of the entity.
	void SetDepth(int depth);

	// Returns the processing depth of the entity.
	int GetDepth();

	// Sets the object's active state.
	// This affects the propagation of children updates.
	void SetActive(bool active);

	// Returns whether the object is active.
	bool IsActive();

	// Returns whether the object is active within the hierarchy.
	bool IsActiveInHierarchy();

	// Adds specified entity as this entity's child.
	// Once registered as child object, NEVER delete it without using the Destroy() method.
	GameObject* AddChild(GameObject* entity);

	// Creates a new GameObject and adds it as a child, then returns it.
	GameObject* CreateChild(std::string name = "");

	// Returns whether the specified object is included as this object's direct child.
	bool ContainsChild(GameObject* entity);

	// Returns the pointer to the list of all children.
	// DO NOT MODIFY THE VECTOR ITSELF!
	std::vector<GameObject*>* GetChildren();

	// Adds the specified component instance to the components list.
	template<class T>
	T* AddComponent(T* component)
	{
		if (component == 0)
		{
			Debug::Log()->Print("GameObject::AddComponent - Attempted to add a null component!");
			return 0;
		}
		// Make sure the object is a type of component.
		if (dynamic_cast<Component*>(component) == 0)
		{
			Debug::Log()->Put("GameObject::AddComponent - component is not a type of Component!: ").Put(typeid(T).name()).Print();
			return 0;
		}
		Component* c = component;
		// Destroying component should be ignored.
		if (c->IsDestroying())
		{
			Debug::Log()->Print("GameObject::AddComponent - Attempted to add a destroying component!");
			return 0;
		}
		// If the component is already attached to an object, return.
		if (c->GetGameObject() != 0)
		{
			Debug::Log()->Print("GameObject::AddComponent - The specified component is already attached to a GameObject!");
			return 0;
		}

		// Set object reference.
		c->AssignObject(this);

		// Insert component to beginning since update is performed on components in reverse-loop order
		// and Transform must be updated first.
		components.insert(components.begin(), c);

		// Init component.
		c->Init();

		// Invoke active event based on this object's state.
		if (IsActiveInHierarchy())
			c->OnActive();
		else
			c->OnInactive();

		// Return component.
		return component;
	}

	// Returns the component of specified type.
	template <class T>
	T* GetComponent()
	{
		for (int i = 0; i < (int)components.size(); i++)
		{
			Component* component = components.at(i);
			if (!component->IsDestroying())
			{
				T* tc = dynamic_cast<T*>(component);
				if (tc != 0)
					return tc;
			}
		}
		return 0;
	}

	// Returns the transform component on this object.
	Transform* GetTransform();

	// Propagates update signal to this object, children objects, and components.
	// This method should NEVER be called manually!
	void PropagateUpdate(float deltaTime);

	// Propagates input update signal to this object, children objects, and components.
	// This method should NEVER be called manually!
	bool PropagateInput();

	// Propagates render signal to children objects and components.
	// This method should NEVER be called manually!
	void PropagateRender(Buffer* buffer);

	// Event called when this object has become active in hierarchy.
	void OnActive();

	// Event called when this object has become inactive in hierarchy.
	void OnInactive();

	void Update(float deltaTime) override;

	void OnDestroy() override;

protected:
	// The parent object in the hierarchy.
	GameObject* parent;

	// Direct access to transform component.
	Transform* transform;

	void PropagateSetActive(bool isEmitter, bool isActive);

	void OnEnable() override;

	void OnDisable() override;

private:
	std::string name;

	// Depth value determines the order of entity update and rendering process.
	int depth;

	// Whether the children list is dirty and needs cleanup.
	bool isChildrenDirty;

	// Whether the gameobject is locally active.
	bool isActive;

	// Counter for the number of parents and self that makes this object inactivein hierarchy.
	int inactiveParents;

	// List of child objects of this object.
	std::vector<GameObject*> children;

	// List of components attached to this object.
	std::vector<Component*> components;


	static bool CompareEntity(GameObject* x, GameObject* y);

	// Invokes OnActive event on this object and its components.
	void InvokeOnActive();

	// Invokes OnInactive event on this object and its components.
	void InvokeOnInactive();
};

#endif