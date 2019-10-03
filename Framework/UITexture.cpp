#include "UITexture.h"

#include "Texture.h"
#include "Buffer.h"

UITexture::UITexture() :
	UIWidget(),
	useUvRect(false),
	texture(0)
{
	uvRect = { 0, 0, 0, 0 };
}

UITexture::~UITexture()
{
	UIWidget::~UIWidget();

	texture = 0;
}

void UITexture::SetTexture(Texture* texture) { this->texture = texture; }

Texture* UITexture::GetTexture() { return texture; }

void UITexture::AdjustToSize()
{
	if (texture == 0)
		return;

	float baseRatio = (float)width / (float)height;
	float imageRatio = (float)texture->GetWidth() / (float)texture->GetHeight();
	// If texture is wider, make height fit.
	if (imageRatio > baseRatio)
	{
		int excessWidth = (texture->GetWidth() - (int)(texture->GetHeight() * baseRatio)) / 2;
		SetUVRect(
			excessWidth,
			0,
			texture->GetWidth() - excessWidth * 2,
			texture->GetHeight()
		);
	}
	// Else if texture is taller, make width fit.
	else
	{
		int excessHeight = (texture->GetHeight() - (int)(texture->GetWidth() / baseRatio)) / 2;
		SetUVRect(
			0,
			excessHeight,
			texture->GetWidth(),
			texture->GetHeight() - excessHeight * 2
		);
	}
	// Make the rendering process take uv rect into account.
	SetEnableUVRect(true);
}

void UITexture::SetUVRect(int x, int y, int w, int h)
{
	uvRect.x = x;
	uvRect.y = y;
	uvRect.w = w;
	uvRect.h = h;
}

void UITexture::SetEnableUVRect(bool useUvRect) { this->useUvRect = useUvRect; }

SDL_Rect UITexture::GetUVRect() { return uvRect; }

void UITexture::Render(Buffer* buffer)
{
	if (texture == 0)
		return;
	UIWidget::Render(buffer);
}

void UITexture::ResetSize()
{
	if (texture != 0)
		SetSize(texture->GetWidth(), texture->GetHeight());
}

void UITexture::Draw(Buffer* buffer, Vector2& scale)
{
	// Retrieve actual texture object.
	SDL_Texture* tex = texture->GetTexture();

	// Assign properties
	SDL_SetTextureColorMod(tex, localColor.r, localColor.g, localColor.b);
	SDL_SetTextureAlphaMod(tex, GetWorldAlpha());

	// Setup source rect with UV rect
	SDL_Rect srcRect;
	if (useUvRect)
	{
		srcRect.x = uvRect.x;
		srcRect.y = uvRect.y;
		srcRect.w = uvRect.w;
		srcRect.h = uvRect.h;
	}
	else
	{
		srcRect.x = srcRect.y = 0;
		srcRect.w = texture->GetWidth();
		srcRect.h = texture->GetHeight();
	}

	// Setup draw desg rect
	SDL_Rect destRect = {
		(int)drawPos.x, (int)drawPos.y,
		(int)actualSize.x, (int)actualSize.y
	};

	buffer->RenderSprite(tex, &srcRect, &destRect);
}