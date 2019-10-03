#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <SDL.h>
#include <string>

struct SDL_Rect;

class Texture
{
public:
	Texture();
	~Texture();

	bool Initialize(std::string spritename, std::string path, SDL_Renderer* renderer);

	int GetWidth() const;
	int GetHeight() const;
	bool HasPatch();
	SDL_Rect GetPatchRect();
	void SetPatchRect(int x, int y, int w, int h);

	std::string GetSpritename();

	SDL_Texture* GetTexture();

private:
	SDL_Texture* texture;

	int width;
	int height;
	bool hasPatch;
	std::string spritename;

	// x = First pixel distance from the left side.
	// y = First pixel distance from the top side.
	// w = Offset from x.
	// h = Offset from y.
	SDL_Rect patchRect;
};

#endif // __TEXTURE_H__
