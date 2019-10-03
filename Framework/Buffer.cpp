#include "Buffer.h"

#include "Debug.h"
#include "Texture.h"
#include "Atlas.h"
#include "Vector2.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

Buffer* Buffer::I = 0;

Buffer::Buffer() :
	window(0),
	renderer(0),
	font(0),
	isFullScreen(false)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		Debug::Log()->Put("Buffer - Failed to initialize SDL").Print();
		return;
	}
	else
	{
		window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);

		if (window == 0)
		{
			Debug::Log()->Put("Buffer - Failed to create SDL window!").Print();
			return;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (renderer == 0)
			{
				Debug::Log()->Put("Buffer - Failed to create SDL renderer!").Print();
				return;
			}
			else
			{
				int imageResult = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

				if (imageResult == 0)
				{
					Debug::Log()->Put("Buffer - Failed to initialize Image module!").Print();
					return;
				}
			}
		}
	}

	if (TTF_Init() != 0)
	{
		Debug::Log()->Put("Buffer - Failed to initialize TTF!").Print();
		return;
	}

	font = TTF_OpenFont("assets\\fonts\\font.ttf", 28);

	SetFullScreen(false);
	SDL_Delay(1000);
	
	Clear();
	FinalizeRender();
}

Buffer::~Buffer()
{
	SDL_DestroyRenderer(renderer);
	renderer = 0;

	SDL_DestroyWindow(window);
	window = 0;

	TTF_CloseFont(font);
	font = 0;

	IMG_Quit();
	SDL_Quit();
}

bool Buffer::Initialize()
{
	if (I != 0)
		return false;
	I = new Buffer();
	return true;
}

void Buffer::Destroy()
{
	if (I != 0)
		delete I;
	I = 0;
}

Buffer* Buffer::GetInstance()
{
	if (I == 0)
	{
		Debug::Log()->Print("Buffer::GetInstance - Not initialized");
		return 0;
	}
	return I;
}

TTF_Font* Buffer::Getfont() { return font; }

SDL_Renderer* Buffer::GetRenderer() { return renderer; }

void Buffer::SetFullScreen(bool isFullscreen)
{
	this->isFullScreen = isFullscreen;
	if (isFullscreen)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALWAYS_ON_TOP);
		SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
		SDL_SetWindowSize(window, Width, Height);
	}
	else
	{
		SDL_SetWindowFullscreen(window, 0);
	}
}
bool Buffer::IsFullScreen() { return isFullScreen; }

void Buffer::Clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Buffer::FinalizeRender()
{
	SDL_RenderPresent(renderer);
}

void Buffer::RenderSprite(SDL_Texture* texture, SDL_Rect* uvRect, SDL_Rect* dest)
{
	if (dest == 0)
		return;

	SDL_RenderCopy(renderer, texture, uvRect, dest);
}

void Buffer::RenderText(SDL_Texture* texture, int* textureWidth, int* textureHeight, SDL_Rect* rect)
{
	if (rect == 0)
		return;

	SDL_Rect src = { 0, 0, *textureWidth, *textureHeight };
	SDL_RenderCopy(renderer, texture, &src, rect);
}