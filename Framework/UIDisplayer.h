#pragma once

#ifndef _UI_DISPLAYER_
#define _UI_DISPLAYER_

#include "Component.h"
#include "GameObject.h"

#include <SDL.h>

class UIDisplayer :
	public Component
{
public:
	UIDisplayer();
	~UIDisplayer() override;

	void Init() override;

	// Sets the alpha value of the displayer.
	virtual void SetAlpha(Uint8 alpha);

	// Sets the alpha value of the displayer in float.
	void SetAlpha(float alpha);

	// Sets the color of the displayer.
	virtual void SetColor(Uint8 r, Uint8 g, Uint8 b);

	// Sets the color of the displayer.
	void SetColor(SDL_Color* color);

	// Returns the color R value of the displayer.
	Uint8 GetColorR();

	// Returns the color G value of the displayer.
	Uint8 GetColorG();

	// Returns the color B value of the displayer.
	Uint8 GetColorB();

	// Returns the alpha value of the displayer.
	Uint8 GetAlpha();

	// Returns the alpha value of the displayer in float.
	float GetAlphaF();

	// Returns the world alpha value of the displayer.
	Uint8 GetWorldAlpha();

	// Returns the world alpha value of the displayer in float.
	float GetWorldAlphaF();

	// Returns the local color of the displayer.
	SDL_Color GetLocalColor();

	// Returns the world color of the displayer.
	SDL_Color GetWorldColor();

protected:
	// Parent displayer object.
	UIDisplayer* parentDisplayer;

	// Local color of the displayer.
	SDL_Color localColor;

private:
};

#endif