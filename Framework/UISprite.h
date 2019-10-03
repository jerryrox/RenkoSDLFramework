#pragma once

#ifndef _UI_SPRITE_
#define _UI_SPRITE_

#include "Vector2.h"
#include "UIWidget.h"
#include "SpriteWrapMode.h"

class Texture;
class Buffer;

class UISprite :
	public UIWidget
{
public:
	UISprite();
	~UISprite() override;

	// Sets the name of the texture to display.
	virtual void SetSpritename(std::string spritename);

	// Returns the sprite name of the current texture.
	std::string GetSpritename();

	// Sets the wrap mode of the sprite.
	virtual void SetWrapMode(SpriteWrapMode mode);

	// Returns the wrap mode currently in use.
	SpriteWrapMode GetWrapMode();

	void ResetSize() override;

	// Sets UV rect for clipping texture.
	void SetUVRect(int x, int y, int w, int h);

	// Sets whether UVRect should be used during rendering.
	void SetEnableUVRect(bool useUvRect);

	// Returns the current UV rect value.
	SDL_Rect GetUVRect();

	void Render(Buffer* buffer) override;

protected:
	// Whether UV rect will be used to partially display the texture.
	bool useUvRect;
	// Rect value used for displaying part of the texture on screen.
	SDL_Rect uvRect;
	// Current texture to be shown on screen.
	Texture* texture;
	// Wrapping mode for the sprite.
	SpriteWrapMode wrapMode;


	void Draw(Buffer* buffer, Vector2& scale) override;

private:
	Vector2 srcDrawSizes[3];
	Vector2 destDrawSizes[3];
};

#endif