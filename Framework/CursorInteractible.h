#pragma once

#ifndef _CURSOR_INTERACTIBLE_
#define _CURSOR_INTERACTIBLE_

#include "GameObject.h"
#include "Events.h"

#include <SDL.h>

class UIWidget;

class CursorInteractible :
	public GameObject
{
public:
	Events Clicked;

	CursorInteractible();
	~CursorInteractible() override;

	void Update(float deltaTime) override;

	bool UpdateInput() override;

	// Sets the cursor detection area's position and size.
	void SetCursorArea(int x, int y, int w, int h);

	// Sets the cursor detection area's position.
	void SetCursorAreaPos(int x, int y);

	// Sets the cursor detection area's size.
	void SetCursorAreaSize(int w, int h);

	// Sets the target widget which the cursor area will be bound to.
	void SetTarget(UIWidget* target);

	// Returns the target widget which the cursor area is being bound to.
	UIWidget* GetTarget();

	// Event called when the cursor has hovered over the cursor area.
	virtual void OnCursorOver();

	// Event called when the cursor has hovered out of the cursor area.
	virtual void OnCursorOut();

	// Event called when the cursor has pressed the area.
	virtual void OnCursorPress();

	// Event called when the cursor has released the area.
	virtual void OnCursorRelease();

	// Event called when the cursor has clicked the area.
	virtual void OnCursorClick();

protected:
	UIWidget* targetWidget;
	SDL_Rect cursorArea;

private:
	bool isPressing;
	bool isCursorOver;

	// Returns whether the cursor is on the area.
	bool IsCursorOnArea();
};

#endif