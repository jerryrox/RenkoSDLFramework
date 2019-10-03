#pragma once

#ifndef _UI_ANIMATED_SPRITE_
#define _UI_ANIMATED_SPRITE_

#include "UISprite.h"
#include "AnimationWrap.h"

class UIAnimatedSprite :
	public UISprite
{
public:
	UIAnimatedSprite();
	~UIAnimatedSprite() override;

	// Starts playing slide animation from beginning.
	void Play();

	// Stops slide animation.
	void Stop();

	// Setup properties related to sliding.
	void SetupSlides(int slidesPerRow, int slidesPerColumn, float fps);

	// Sets wrap mode
	void SetAnimationWrap(AnimationWrap wrapMode);

	// Sets the current slide index.
	void SetSlide(int xIndex, int yIndex);

	void SetSpritename(std::string spritename) override;

	void SetWrapMode(SpriteWrapMode wrapMode) override;

	void Update(float deltaTime) override;

private:
	bool isPlaying;
	int slideCount;
	int slidesPerRow;
	int slidesPerColumn;
	float slideTime;
	AnimationWrap wrapMode;

	int curXIndex;
	int curYIndex;
	int widthPerSlide;
	int heightPerSlide;
	float curSlideTime;

	void CacheUVProperties();
	void ResetUV();
};

#endif