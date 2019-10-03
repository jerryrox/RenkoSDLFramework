#include "texture.h"

#include "Debug.h"
#include <SDL_image.h>
#include <cassert>

Texture::Texture() :
	texture(0),
	width(0),
	height(0),
	hasPatch(false)
{
}

Texture::~Texture()
{
	if (texture != 0)
	{
		SDL_DestroyTexture(texture);
	}
	texture = 0;
}

bool Texture::Initialize(std::string spritename, std::string path, SDL_Renderer* renderer)
{
	this->spritename = spritename;

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == 0)
	{
		Debug::Log()->Put("Failed to load image from path: ").Put(path).Print();
		return false;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (texture == 0)
		{
			Debug::Log()->Put("Failed to create texture!").Print();
			return false;
		}

		SDL_FreeSurface(surface);
	}

	SDL_QueryTexture(texture, 0, 0, &width, &height);

	// Set default patch value.
	SetPatchRect(0, 0, width, height);
	hasPatch = false;

	return texture != 0;
}

int Texture::GetWidth() const { return width; }

int Texture::GetHeight() const { return height; }

bool Texture::HasPatch() { return hasPatch; }

SDL_Rect Texture::GetPatchRect() { return patchRect; }

void Texture::SetPatchRect(int x, int y, int w, int h)
{
	hasPatch = true;
	patchRect.x = x;
	patchRect.y = y;
	patchRect.w = w;
	patchRect.h = h;
}

std::string Texture::GetSpritename() { return spritename.c_str(); }

SDL_Texture* Texture::GetTexture() { return texture; }
