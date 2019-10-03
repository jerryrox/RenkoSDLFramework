#include "UISprite.h"

#include "Buffer.h"
#include "Texture.h"
#include "Atlas.h"
#include "CursorInteractible.h"

UISprite::UISprite() :
	UIWidget(),
	useUvRect(false),
	texture(0),
	wrapMode(SpriteWrapMode::Sprite_Simple)
{
	uvRect = { 0, 0, 0, 0 };
}

UISprite::~UISprite()
{
	UIWidget::~UIWidget();

	texture = 0;
}

void UISprite::SetSpritename(std::string spritename)
{
	auto atlas = Atlas::GetInstance();
	if (atlas == 0)
		return;
	texture = atlas->GetTexture(spritename);
}

std::string UISprite::GetSpritename()
{
	if (texture == 0)
		return 0;
	return texture->GetSpritename();
}

void UISprite::SetWrapMode(SpriteWrapMode mode) { wrapMode = mode; }

SpriteWrapMode UISprite::GetWrapMode() { return wrapMode; }

void UISprite::ResetSize()
{
	if (texture != 0)
		SetSize(texture->GetWidth(), texture->GetHeight());
}

void UISprite::SetUVRect(int x, int y, int w, int h)
{
	uvRect.x = x;
	uvRect.y = y;
	uvRect.w = w;
	uvRect.h = h;
}

void UISprite::SetEnableUVRect(bool useUvRect) { this->useUvRect = useUvRect; }

SDL_Rect UISprite::GetUVRect() { return uvRect; }

void UISprite::Render(Buffer* buffer)
{
	if (texture == 0)
		return;

	UIWidget::Render(buffer);
}

void UISprite::Draw(Buffer* buffer, Vector2& scale)
{
	// Retrieve actual texture object.
	SDL_Texture* tex = texture->GetTexture();

	// Assign properties
	SDL_SetTextureColorMod(tex, localColor.r, localColor.g, localColor.b);
	SDL_SetTextureAlphaMod(tex, GetWorldAlpha());

	// Set to buffer.
	if (wrapMode == SpriteWrapMode::Sprite_Simple)
	{
		// Calculate destination rect
		SDL_Rect destRect = {
			(int)drawPos.x, (int)drawPos.y,
			(int)actualSize.x, (int)actualSize.y
		};
		buffer->RenderSprite(tex, useUvRect ? &uvRect : 0, &destRect);
	}
	else
	{
		// If width is 0, don't render.
		if (actualSize.x < 1)
			return;

		SDL_Rect patch = texture->GetPatchRect();

		srcDrawSizes[0].x = (float)patch.x;
		srcDrawSizes[0].y = (float)patch.y;
		srcDrawSizes[1].x = (float)patch.w;
		srcDrawSizes[1].y = (float)patch.h;
		srcDrawSizes[2].x = (float)(texture->GetWidth() - patch.x - patch.w);
		srcDrawSizes[2].y = (float)(texture->GetHeight() - patch.y - patch.h);

		destDrawSizes[0].x = srcDrawSizes[0].x * scale.x;//fminf(srcDrawSizes[0].x, srcDrawSizes[0].x * scale.x);
		destDrawSizes[0].y = srcDrawSizes[0].y * scale.y;//fminf(srcDrawSizes[0].y, srcDrawSizes[0].y * scale.y);
		destDrawSizes[2].x = srcDrawSizes[2].x * scale.x;//fminf(srcDrawSizes[2].x, srcDrawSizes[2].x * scale.x);
		destDrawSizes[2].y = srcDrawSizes[2].y * scale.y;//fminf(srcDrawSizes[2].y, srcDrawSizes[2].y * scale.y);
		destDrawSizes[1].x = actualSize.x - destDrawSizes[0].x - destDrawSizes[2].x;
		destDrawSizes[1].y = actualSize.y - destDrawSizes[0].y - destDrawSizes[2].y;
		
		SDL_Rect drawSrc = { 0, 0, 0, 0 };
		SDL_Rect drawDest = { 0, (int)drawPos.y, 0, 0 };
		for (int r = 0; r < 3; r++)
		{
			drawSrc.x = 0;
			drawDest.x = (int)drawPos.x;
			for (int c = 0; c < 3; c++)
			{
				drawSrc.w = (int)srcDrawSizes[c].x;
				drawSrc.h = (int)srcDrawSizes[r].y;
				drawDest.w = (int)destDrawSizes[c].x;
				drawDest.h = (int)destDrawSizes[r].y;
				buffer->RenderSprite(tex, &drawSrc, &drawDest);

				drawSrc.x += (int)srcDrawSizes[c].x;
				drawDest.x += (int)destDrawSizes[c].x;
			}
			drawSrc.y += (int)srcDrawSizes[r].y;
			drawDest.y += (int)destDrawSizes[r].y;
		}
	}
}