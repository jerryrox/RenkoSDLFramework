#pragma once

#ifndef _BUFFER_
#define _BUFFER_

#include "SpriteWrapMode.h"
#include <string>
#include <SDL_ttf.h>

struct SDL_Rect;
struct SDL_Color;
struct SDL_Window;
struct SDL_Renderer;
struct Vector2;
class Texture;
class Atlas;

class Buffer
{
public:
	static const int Width = 1280;
	static const int Height = 720;

	static bool Initialize();
	static void Destroy();
	static Buffer* GetInstance();

	static float GetScreenRatio() { return (float)Width / (float)Height; }

	TTF_Font* Getfont();
	SDL_Renderer* GetRenderer();

	void SetFullScreen(bool isFullscreen);
	bool IsFullScreen();

	void Clear();
	void FinalizeRender();

	// Renders sprite on screen.
	void RenderSprite(SDL_Texture* texture, SDL_Rect* uvRect, SDL_Rect* dest);

	// Renders text on screen.
	// Rect should refer to a value which has its drawing position and width/height already setup.
	void RenderText(SDL_Texture* texture, int* textureWidth, int* textureHeight, SDL_Rect* rect);

private:
	static Buffer* I;

	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;

	bool isFullScreen;

	Buffer();
	~Buffer();
};

#endif