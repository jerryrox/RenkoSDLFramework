#pragma once

#ifndef _UI_TEXTURE_
#define _UI_TEXTURE_

#include "UIWidget.h"

class Texture;

class UITexture :
	public UIWidget
{
public:
	UITexture();
	~UITexture() override;

	// Sets the texture to be displayed.
	void SetTexture(Texture* texture);

	// Returns the texture being displayed.
	Texture* GetTexture();

	// Adjusts UV rect values to make image show at its original ratio.
	// Think of it as filling within the current size.
	void AdjustToSize();

	// Sets UV rect for clipping texture.
	void SetUVRect(int x, int y, int w, int h);

	// Sets whether UVRect should be used during rendering.
	void SetEnableUVRect(bool useUvRect);

	// Returns the current UV rect value.
	SDL_Rect GetUVRect();

	void Render(Buffer* buffer) override;

	void ResetSize() override;

protected:
	void Draw(Buffer* buffer, Vector2& scale) override;

private:
	// Whether UV rect will be used to partially display the texture.
	bool useUvRect;
	// Rect value used for displaying part of the texture on screen.
	SDL_Rect uvRect;
	// Current texture to be shown on screen.
	Texture* texture;
};

#endif