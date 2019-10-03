#include "AnimeEventSection.h"

#include "Anime.h"

AnimeEventSection::AnimeEventSection(Anime* anime, int frame, std::function<void(void)> callback) :
	AnimeSection(0, frame, frame, Linear, 0)
{
	this->callback = callback;
	this->anime = anime;
}

AnimeEventSection::~AnimeEventSection()
{
	callback = 0;
	anime = 0;
}

void AnimeEventSection::ActivateState()
{
	// Events must only process during playing state.
	if (!anime->IsPlaying())
		return;

	if (curFrame >= from && lastFrame < from)
		callback();
}