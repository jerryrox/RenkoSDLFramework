#pragma once

#ifndef _UI_WIDGET_
#define _UI_WIDGET_

#include "UIDisplayer.h"
#include "Vector2.h"
#include "Pivot.h"

#include <SDL.h>

class UIWidget :
	public UIDisplayer
{
public:
	UIWidget();
	~UIWidget() override;

	// Sets the width of the widget.
	void SetWidth(int width);

	// Sets the height of the widget.
	void SetHeight(int height);

	// Sets the width and height of the widget.
	virtual void SetSize(int width, int height);

	// Resets the size to its natural value.
	virtual void ResetSize() = 0;

	// Returns the draw width.
	int GetWidth();

	// Returns the draw height.
	int GetHeight();

	// Returns the top-left corner position where the widget will be drawn from.
	Vector2 GetDrawPosition();

	// Returns the actual size of the widget when drawn on the screen.
	Vector2 GetActualSize();

	// Sets the pivot point for drawing the widget.
	void SetPivot(Pivot pivot);

	// Returns the current pivot point used for drawing.
	Pivot GetPivot();

	void Render(Buffer* buffer) override;

protected:
	// Width of the rendered widget.
	int width;

	// Height of the rendered widget.
	int height;

	// Drawing pivot of the widget.
	Pivot pivot;

	// Additional scale value to apply.
	float customScale;

	// The top-left corner of the drawing point.
	Vector2 drawPos;

	// The actual size drawn on the screen.
	Vector2 actualSize;

	// Performs drawing of whatever element it's specialized in drawing.
	virtual void Draw(Buffer* buffer, Vector2& scale) = 0;
};

#endif