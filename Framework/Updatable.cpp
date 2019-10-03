#include "Updatable.h"

Updatable::Updatable() :
	isEnabled(true),
	isDestroying(false)
{
}

Updatable::~Updatable()
{
}

void Updatable::Init() {}

void Updatable::SetEnable(bool enabled)
{
	this->isEnabled = enabled;
	if (isEnabled)
		OnEnable();
	else
		OnDisable();
}

bool Updatable::IsEnabled() { return isEnabled; }

void Updatable::Destroy()
{
	isDestroying = true;
}

bool Updatable::IsDestroying() { return isDestroying; }

bool Updatable::UpdateInput() { return true; }

