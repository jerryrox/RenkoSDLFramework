#pragma once

#ifndef _ANIME_EVENT_SECTION_
#define _ANIME_EVENT_SECTION_

#include "AnimeSection.h"
#include <functional>

class Anime;

class AnimeEventSection :
	public AnimeSection
{
public:
	AnimeEventSection(Anime* anime, int frame, std::function<void(void)> callback);
	~AnimeEventSection();

protected:
	void ActivateState() override;

private:
	std::function<void(void)> callback;
	Anime* anime;
};

#endif