#include "GameObject.h"

#include "Component.h"
#include "Transform.h"

#include <algorithm>

GameObject::GameObject() : GameObject("")
{
}

GameObject::GameObject(std::string name) :
	Updatable(),
	parent(0),
	transform(0),
	name(),
	depth(0),
	isChildrenDirty(false),
	isActive(true),
	inactiveParents(0)
{
	this->name = name;
}

GameObject::~GameObject()
{
	Updatable::~Updatable();

	for (int i = 0; i < (int)components.size(); i++)
	{
		Component* component = components.at(i);
		component->Destroy();
		component->OnDestroy();
		delete component;
	}
	components.clear();

	for (int i = 0; i < (int)children.size(); i++)
	{
		GameObject* child = children.at(i);
		child->Destroy();
		child->OnDestroy();
		delete child;
	}
	children.clear();

	parent = 0;
}

void GameObject::Init()
{
	transform = AddComponent(new Transform(parent == 0 ? 0 : parent->transform));
}

std::string GameObject::GetName() { return name; }

GameObject* GameObject::GetParent() { return parent; }

void GameObject::SetDepth(int depth)
{
	if (this->depth != depth)
	{
		this->depth = depth;
		if (parent != 0)
			parent->isChildrenDirty = true;
	}
}

int GameObject::GetDepth() { return depth; }

void GameObject::SetActive(bool active)
{
	// Handle only if change.
	if (isActive != active)
	{
		isActive = active;
		// If no parents are inactive, proceed with event invocation.
		if (inactiveParents <= 0)
		{
			if (isActive)
				InvokeOnActive();
			else
				InvokeOnInactive();
		}

		// Propagate active signal to all children objects.
		PropagateSetActive(true, isActive);
	}
}

bool GameObject::IsActive() { return isActive; }

bool GameObject::IsActiveInHierarchy() { return isActive && inactiveParents <= 0; }

GameObject* GameObject::AddChild(GameObject* entity)
{
	if (entity == 0)
	{
		Debug::Log()->Print("GameObject::AddChild - Specified entity is null!");
		return 0;
	}
	if (entity->isDestroying)
	{
		Debug::Log()->Print("GameObject::AddChild - Attempted to add an object whose destroy flag is true!");
		return 0;
	}
	// If the child is already included somewhere in the hierarchy, ignore it.
	if (entity->parent != 0)
	{
		Debug::Log()->Print("GameObject::AddChild - Attempted to add an object which is already placed somewhere in the hierarchy!");
		return 0;
	}

	// Add the object as child.
	entity->parent = this;
	children.push_back(entity);

	// Invoke initialization.
	entity->Init();

	// Inherit active state and invoke event.
	entity->inactiveParents = this->inactiveParents + (this->isActive ? 0 : 1);
	if (entity->inactiveParents == 0)
		entity->InvokeOnActive();
	else
		entity->InvokeOnInactive();

	// Cleanse children list.
	isChildrenDirty = true;
	return entity;
}

GameObject* GameObject::CreateChild(std::string name) { return AddChild(new GameObject(name)); }

bool GameObject::ContainsChild(GameObject* entity)
{
	return std::find(children.begin(), children.end(), entity) != children.end();
}

std::vector<GameObject*>* GameObject::GetChildren() { return &children; }

Transform* GameObject::GetTransform() { return transform; }

void GameObject::PropagateUpdate(float deltaTime)
{
	// Inactive, no update.
	if (!isActive)
		return;

	// If self is enabled, do update.
	if (isEnabled)
		Update(deltaTime);
	// Handle update on components if enabled.
	for (int i = (int)components.size() - 1; i >= 0; i--)
	{
		Component* component = components.at(i);
		// Destroy component?
		if (component->IsDestroying())
		{
			component->OnDestroy();
			components.erase(components.begin() + i);
			delete component;
			continue;
		}
		// Update component.
		if (component->IsEnabled())
			component->Update(deltaTime);
	}

	// Cleanse children list if dirty.
	if (isChildrenDirty)
	{
		isChildrenDirty = false;
		// Sort children by depth, ascending.
		std::sort(children.begin(), children.end(), CompareEntity);
	}

	// Propagate update to children.
	// Loop is reversed because objects created during this process shouldn't be updated until the next frame.
	for (int i = (int)children.size() - 1; i >= 0; i--)
	{
		GameObject* child = children.at(i);
		// Destroy child?
		if (child->isDestroying)
		{
			child->OnDestroy();
			children.erase(children.begin() + i);
			delete child;
			continue;
		}
		// Propagate update.
		child->PropagateUpdate(deltaTime);
	}
}

bool GameObject::PropagateInput()
{
	// If inactive, return.
	if (!isActive)
		return true;

	// Send input to children from highest depth first.
	for (int i = (int)children.size() - 1; i >= 0; i--)
	{
		GameObject* child = children.at(i);
		// If child wishes to consume input, just return.
		if (!child->PropagateInput())
			return false;
	}

	// Send update signal to components.
    // When processing input for components, the return value from UpdateInput will toggle whether
    // input propagation should be stopped, instead of immediately returning.
	bool shouldStop = false;
	for (int i = 0; i < (int)components.size(); i++)
	{
		Component* component = components.at(i);
		if (component->IsEnabled())
			shouldStop |= !component->UpdateInput();
	}

	// Perform input update on the object itself.
	if (isEnabled)
		shouldStop |= !UpdateInput();

	// Return whether input was consumed or not.
	return !shouldStop;
}

void GameObject::PropagateRender(Buffer* buffer)
{
	// If this object is inactive, return.
	if (!isActive)
		return;
	// Let components render their stuffs.
	for (int i = 0; i < (int)components.size(); i++)
	{
		Component* component = components.at(i);
		if (component->IsEnabled())
			component->Render(buffer);
	}
	// Propagate render signal to children.
	for (int i = 0; i < (int)children.size(); i++)
		children.at(i)->PropagateRender(buffer);
}

void GameObject::OnActive() {}

void GameObject::OnInactive() {}

void GameObject::Update(float deltaTime) {}

void GameObject::OnDestroy() {}

void GameObject::PropagateSetActive(bool isEmitter, bool isActive)
{
	// Apply it localy if not the emitter.
	if (!isEmitter)
	{
		inactiveParents += isActive ? -1 : 1;

		// Invoke events based on implicit activation/deactivation.
		// Child active, parent active, all parents active
		if (this->isActive && isActive && inactiveParents == 0)
			InvokeOnActive();
		// Child active, parent inactive, one parent inactive)
		else if (this->isActive && !isActive && inactiveParents == 1)
			InvokeOnInactive();
	}
	// Propagate to children.
	for (int i = (int)children.size() - 1; i >= 0; i--)
		children.at(i)->PropagateSetActive(false, isActive);
}

void GameObject::OnEnable() {}

void GameObject::OnDisable() {}

bool GameObject::CompareEntity(GameObject* x, GameObject* y) { return x->depth < y->depth; }

void GameObject::InvokeOnActive()
{
	OnActive();
	for (int i = 0; i < (int)components.size(); i++)
	{
		Component* component = components.at(i);
		if (!component->IsDestroying())
			component->OnActive();
	}
}

void GameObject::InvokeOnInactive()
{
	OnInactive();
	for (int i = 0; i < (int)components.size(); i++)
	{
		Component* component = components.at(i);
		if (!component->IsDestroying())
			component->OnInactive();
	}
}