#include "Animator.h"

#include "Anime.h"
#include "Debug.h"

Animator::Animator() :
	Component()
{
}

Animator::~Animator()
{
	Component::~Component();

	std::map<std::string, Anime*>::iterator i;
	for (i = animations.begin(); i != animations.end(); i++)
		delete i->second;
	animations.clear();
}

void Animator::Update(float deltaTime)
{
	// Simply update all animations.
	std::map<std::string, Anime*>::iterator i;
	for (i = animations.begin(); i != animations.end(); i++)
	{
		i->second->Update(deltaTime);
	}
}

Anime* Animator::CreateAnime(std::string name)
{
	// Already exists.
	if (GetAnime(name) != 0)
	{
		Debug::Log()->Put("Animator::CreateAnime - Animation already exists for name: ").Put(name).Print();
		return 0;
	}
	// Create anime and return it.
	Anime* anime = new Anime();
	animations.emplace(name, anime);
	return anime;
}

inline Anime* Animator::GetAnime(std::string name)
{
	if (animations.find(name) != animations.end())
		return animations[name];
	return 0;
}

void Animator::RemoveAnime(std::string name, bool shouldDelete)
{
	Anime* anime = GetAnime(name);
	if (anime == 0)
		return;
	if(shouldDelete)
		delete anime;
	animations.erase(name);
}

void Animator::StopAll()
{
	std::map<std::string, Anime*>::iterator i;
	for (i = animations.begin(); i != animations.end(); i++)
		i->second->Stop();
}