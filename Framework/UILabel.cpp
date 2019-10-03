#include "UILabel.h"

#include "Debug.h"
#include "Buffer.h"
#include "Transform.h"
#include "CursorInteractible.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

UILabel::UILabel() :
	UIWidget(),
	text(""),
	overflow(TextOverflow::Overflow_Free),
	shouldRebuild(true),
	surface(0),
	texture(0),
	textureWidth(0),
	textureHeight(0),
	wrapWidth(1280)
{
}

UILabel::~UILabel()
{
	UIWidget::~UIWidget();

	Dispose();
}

void UILabel::SetFontSize(float size)
{
	// Let the Render method perform the scaling.
	customScale = size / 28.0f;
}

void UILabel::SetText(std::string text)
{
	this->text = text;
	shouldRebuild = true;
}

std::string UILabel::GetText() { return text; }

void UILabel::SetWrapSize(Uint32 width)
{
	wrapWidth = width;
	shouldRebuild = true;
}

void UILabel::SetOverflow(TextOverflow overflow)
{
	this->overflow = overflow;
}

TextOverflow UILabel::GetOverflow() { return overflow; }

void UILabel::SetSize(int width, int height)
{
	if (overflow == TextOverflow::Overflow_Free)
		return;
	UIWidget::SetSize(width, height);
}

void UILabel::ResetSize()
{
	SetSize(textureWidth, textureHeight);
}

void UILabel::Render(Buffer* buffer)
{
	if (shouldRebuild)
		RebuildTexture(buffer);
	if (texture == 0)
		return;

	UIWidget::Render(buffer);
}

void UILabel::Draw(Buffer* buffer, Vector2& scale)
{
	// Assign properties
	SDL_SetTextureColorMod(texture, localColor.r, localColor.g, localColor.b);
	SDL_SetTextureAlphaMod(texture, GetWorldAlpha());

	// Calculate final rect
	SDL_Rect rect = {
		(int)drawPos.x, (int)drawPos.y,
		(int)actualSize.x, (int)actualSize.y
	};

	// Set to buffer.
	buffer->RenderText(texture, &textureWidth, &textureHeight, &rect);
}

void UILabel::RebuildTexture(Buffer* buffer)
{
	// Dispose previous texture
	Dispose();

	// Rebuild texture and surface.
	// During this, alpha must be kept consistent at 255.
	auto cachedAlpha = localColor.a;
	localColor.a = 255;
	surface = TTF_RenderText_Blended_Wrapped(buffer->Getfont(), text.c_str(), localColor, wrapWidth);
	localColor.a = cachedAlpha;
	texture = SDL_CreateTextureFromSurface(buffer->GetRenderer(), surface);

	// Cache texture width and height.
	SDL_QueryTexture(texture, 0, 0, &textureWidth, &textureHeight);

	// Set draw size equal to texture if free overflow.
	// Because UILabel's SetSize should not allow setting size when overflow is free,
	// we access the base class directly.
	if (overflow == TextOverflow::Overflow_Free)
		UIWidget::SetSize(textureWidth, textureHeight);
}

void UILabel::Dispose()
{
	if (texture != 0)
		SDL_DestroyTexture(texture);
	texture = 0;

	if (surface != 0)
		SDL_FreeSurface(surface);
	surface = 0;
}