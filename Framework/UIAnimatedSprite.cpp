#include "UIAnimatedSprite.h"

#include "Debug.h"

#include "Texture.h"

UIAnimatedSprite::UIAnimatedSprite() :
	UISprite(),
	isPlaying(false),
	slideCount(0),
	slidesPerRow(1),
	slidesPerColumn(1),
	slideTime(0),
	wrapMode(AnimationWrap::Wrap_Loop),
	curXIndex(0),
	curYIndex(0),
	widthPerSlide(100),
	heightPerSlide(100),
	curSlideTime(0)
{
	SetEnableUVRect(true);
}

UIAnimatedSprite::~UIAnimatedSprite()
{
	UISprite::~UISprite();
}

void UIAnimatedSprite::Play()
{
	isPlaying = true;
	curXIndex = 0;
	curYIndex = 0;
	curSlideTime = 0;
}

void UIAnimatedSprite::Stop()
{
	isPlaying = false;
}

void UIAnimatedSprite::SetupSlides(int slidesPerRow, int slidesPerColumn, float fps)
{
	this->slidesPerRow = slidesPerRow;
	this->slidesPerColumn = slidesPerColumn;
	slideCount = slidesPerRow * slidesPerColumn;
	slideTime = 1.0f / fps;

	CacheUVProperties();
	ResetUV();
}

void UIAnimatedSprite::SetAnimationWrap(AnimationWrap wrapMode) { this->wrapMode = wrapMode; }

void UIAnimatedSprite::SetSlide(int xIndex, int yIndex)
{
	if (xIndex < 0)
		xIndex = 0;
	else if (xIndex >= slidesPerRow)
		xIndex = slidesPerRow - 1;
	if (yIndex < 0)
		yIndex = 0;
	else if (yIndex >= slidesPerColumn)
		yIndex = slidesPerColumn - 1;

	curXIndex = xIndex;
	curYIndex = yIndex;
	ResetUV();
}

void UIAnimatedSprite::SetSpritename(std::string spritename)
{
	UISprite::SetSpritename(spritename);

	if (texture != 0)
	{
		CacheUVProperties();
		ResetUV();
	}
}

void UIAnimatedSprite::SetWrapMode(SpriteWrapMode wrapMode)
{
	// Only simple sprites support UV rect!
	UISprite::SetWrapMode(SpriteWrapMode::Sprite_Simple);
}

void UIAnimatedSprite::Update(float deltaTime)
{
	if (!isPlaying)
		return;

	curSlideTime += deltaTime;
	// Next frame
	if (curSlideTime >= slideTime)
	{
		curSlideTime -= slideTime;

		curXIndex++;
		if (curXIndex >= slidesPerRow)
		{
			curXIndex = 0;
			curYIndex++;
			// End of frame
			if (curYIndex >= slidesPerColumn)
			{
				switch (wrapMode)
				{
				case Wrap_None:
					Stop();
					break;
				case Wrap_Reset:
					curXIndex = 0;
					curYIndex = 0;
					Stop();
					break;
				case Wrap_Loop:
					curYIndex = 0;
					break;
				}
			}
		}

		// Set UV rect
		ResetUV();
	}
}

void UIAnimatedSprite::CacheUVProperties()
{
	widthPerSlide = texture->GetWidth() / slidesPerRow;
	heightPerSlide = texture->GetHeight() / slidesPerColumn;
}

void UIAnimatedSprite::ResetUV()
{
	SetUVRect(curXIndex * widthPerSlide, curYIndex * heightPerSlide, widthPerSlide, heightPerSlide);
}