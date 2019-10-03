#include "InputBlocker.h"

InputBlocker::InputBlocker() :
	GameObject()
{
}

InputBlocker::~InputBlocker()
{
	GameObject::~GameObject();
}

void InputBlocker::Init()
{
	GameObject::Init();

	// Set to highest depth.
	SetDepth(INT_MAX);
}

bool InputBlocker::UpdateInput() { return false; }