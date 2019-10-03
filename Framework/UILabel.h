#pragma once

#ifndef _UI_LABEL_
#define _UI_LABEL_

#include "UIWidget.h"
#include "TextOverflow.h"

#include <SDL.h>

class UILabel :
	public UIWidget
{
public:
	UILabel();
	~UILabel() override;

	// Sets the size of the font.
	void SetFontSize(float size);

	// Sets the text to be displayed.
	void SetText(std::string text);

	// Returns the text being displayed.
	std::string GetText();

	// Sets the width size which forces long-running texts fall over to next line on overflow.
	void SetWrapSize(Uint32 width);

	// Sets the overflow mode for the text.
	void SetOverflow(TextOverflow overflow);

	// Returns the text overflow method being used.
	TextOverflow GetOverflow();

	void SetSize(int width, int height) override;

	void ResetSize() override;

	void Render(Buffer* buffer) override;


protected:
	void Draw(Buffer* buffer, Vector2& scale) override;

private:
	// The text value to be drawn on screen.
	std::string text;
	// How overlflown text should be displayed.
	TextOverflow overflow;
	// Whether text is dirty and should be rebuilt.
	bool shouldRebuild;
	// Cached image data for performance.
	SDL_Surface* surface;
	SDL_Texture* texture;
	// Original width of the texture.
	int textureWidth;
	// Original height of the texture.
	int textureHeight;
	// Width of the wrapped text.
	Uint32 wrapWidth;

	// Rebuilds texture for the text.
	void RebuildTexture(Buffer* buffer);

	// Disposes temporary texture and surface for texture rebuilding.
	void Dispose();
};

#endif