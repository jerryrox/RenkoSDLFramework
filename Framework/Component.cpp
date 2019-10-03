#include "Component.h"

#include "GameObject.h"
#include "Debug.h"

Component::Component() :
	Updatable(),
	gameObject(0)
{
}

Component::~Component()
{
	Updatable::~Updatable();

	gameObject = 0;
}

GameObject* Component::GetGameObject() { return gameObject; }

Transform* Component::GetTransform() { return gameObject->GetTransform(); }

void Component::AssignObject(GameObject* object)
{
	if (gameObject == 0)
		gameObject = object;
}

void Component::Render(Buffer* buffer) {}

void Component::OnActive() {}

void Component::OnInactive() {}

void Component::Update(float deltaTime) {}

void Component::OnDestroy() {}

void Component::OnEnable() {}

void Component::OnDisable() {}