#pragma once

#ifndef _ATLAS_
#define _ATLAS_

#include <map>
#include <string>

struct SDL_Rect;
struct SDL_Renderer;
class Texture;

class Atlas
{
public:
	Atlas();
	~Atlas();

	static bool Initialize(SDL_Renderer* renderer);
	static void Destroy();

	static Atlas* GetInstance();

	Texture* GetTexture(std::string spritename);

	// Loads the texture of specified spritename.
	void LoadTexture(std::string spritename, std::string extension);

	// Loads the texture of specified spritename with 9-patching.
	// X = Pixels from left side.
	// Y = Pixels from top side.
	// Z = Pixels from X.
	// W = Pixels from Y.
	void LoadTexture(std::string spritename, std::string extension, int x, int y, int z, int w);

	// Loads a texture which is not a standard part of the game.
	// By using this, the caller must manage the returned texture on their own.
	Texture* LoadRawTexture(std::string path);


private:
	static Atlas* I;

	SDL_Renderer* renderer;
	std::map<std::string, Texture*> atlas;
};

#endif