#include "Atlas.h"

#include "Debug.h"
#include "Texture.h"
#include <SDL_render.h>

Atlas* Atlas::I = 0;

Atlas::Atlas()
{
}

Atlas::~Atlas()
{
	std::map<std::string, Texture*>::iterator i;
	for (i = atlas.begin(); i != atlas.end(); i++)
	{
		delete i->second;
	}
	atlas.clear();
}

bool Atlas::Initialize(SDL_Renderer* renderer)
{
	if (I != 0)
		return false;

	I = new Atlas();
	I->renderer = renderer;

	return true;
}

void Atlas::Destroy()
{
	if (I != 0)
		delete I;
	I = 0;
}

Atlas* Atlas::GetInstance() { return I; }

Texture* Atlas::GetTexture(std::string spritename)
{
	// None exists
	if (atlas.find(spritename) == atlas.end())
	{
		Debug::Log()->Put("Atlas::GetTexture - No spritename not registered: ").Put(spritename).Print();
		return 0;
	}
	return atlas[spritename];
}

void Atlas::LoadTexture(std::string spritename, std::string extension)
{
	std::string fullPath("assets\\images\\");
	fullPath.append(spritename).append(extension);

	Texture* texture = new Texture();
	if (!texture->Initialize(spritename, fullPath.c_str(), renderer))
	{
		Debug::Log()->Put("Failed to load texture from: ").Put(fullPath).Print();
		delete texture;
		return;
	}
	atlas[spritename] = texture;
}

void Atlas::LoadTexture(std::string spritename, std::string extension, int x, int y, int z, int w)
{
	std::string fullPath("assets\\images\\");
	fullPath.append(spritename).append(extension);

	Texture* texture = new Texture();
	if (!texture->Initialize(spritename, fullPath.c_str(), renderer))
	{
		Debug::Log()->Put("Failed to load texture from: ").Put(fullPath).Print();
		delete texture;
		return;
	}
	texture->SetPatchRect(x, y, z, w);
	atlas[spritename] = texture;
}

Texture* Atlas::LoadRawTexture(std::string path)
{
	Texture* texture = new Texture();
	if (!texture->Initialize("", path, renderer))
	{
		delete texture;
		return 0;
	}
	return texture;
}