#pragma once

#ifndef _INPUT_
#define _INPUT_

#include "Vector2.h"


#include <SDL_joystick.h>
#include <functional>
#include <vector>
#include <SDL.h>

// Some controller button codes are not consistent!
typedef enum
{
	CONTROLLER_BUTTON_LEFTSHOULDER = 4,
	CONTROLLER_BUTTON_RIGHTSHOULDER = 5,
	CONTROLLER_BUTTON_START = 7

} ConsistentControllerButton;


class Input
{
public:
	static bool Initialize();
	static void Destroy();
	static Input* GetInstance();

	// Returns whether specified keyboard key is down.
	static bool IsKeyDown(SDL_Keycode code);
	// Returns whether specified joystick button is down.
	// Refer to SDL_CONTROLLER_BUTTON_{ButtonInitial} or,
	// CONTROLLER_BUTTON_{ButtonInitial} for other shoulders and start button.
	static bool IsButtonDown(Uint8 code);
	// Returns whether specified hat is down.
	// Refer to SDL_HAT_{Direction}
	static bool IsHatDown(Uint8 code);

	// Returns whether specified keyboard key is up.
	static bool IsKeyUp(SDL_Keycode code);
	// Returns whether specified joystick button is up.
	// Refer to SDL_CONTROLLER_BUTTON_{ButtonInitial} or,
	// CONTROLLER_BUTTON_{ButtonInitial} for other shoulders and start button.
	static bool IsButtonUp(Uint8 code);
	// Returns whether specified hat is up.
	// Refer to SDL_HAT_{Direction}
	static bool IsHatUp(Uint8 code);

	// Returns whether specified keyboard key is held.
	static bool IsKeyHold(SDL_Keycode code);
	// Returns whether specified joystick button is held.
	// Refer to SDL_CONTROLLER_BUTTON_{ButtonInitial} or,
	// CONTROLLER_BUTTON_{ButtonInitial} for other shoulders and start button.
	static bool IsButtonHold(Uint8 code);
	// Returns whether specified hat is held.
	// Refer to SDL_HAT_{Direction}
	static bool IsHatHold(Uint8 code);

	// Returns whether any keyboard key is down.
	static bool IsAnyKeyDown();
	// Returns whether any joystick button is down.
	// Refer to SDL_CONTROLLER_BUTTON_{ButtonInitial}
	static bool IsAnyButtonDown();
	// Returns whether any hat is down.
	// Refer to SDL_HAT_{Direction}
	static bool IsAnyHatDown();

	// Returns whether any keyboard key is up.
	static bool IsAnyKeyUp();
	// Returns whether any joystick button is up.
	// Refer to SDL_CONTROLLER_BUTTON_{ButtonInitial}
	static bool IsAnyButtonUp();
	// Returns whether any hat is up.
	// Refer to SDL_HAT_{Direction}
	static bool IsAnyHatUp();

	// Returns whether any keyboard key is held.
	static bool IsAnyKeyHold();
	// Returns whether any joystick button is held.
	// Refer to SDL_CONTROLLER_BUTTON_{ButtonInitial}
	static bool IsAnyButtonHold();
	// Returns whether any hat is held.
	// Refer to SDL_HAT_{Direction}
	static bool IsAnyHatHold();

	// Returns whether a mouse button is down.
	static bool IsMouseDown();
	// Returns whether a mouse button is up.
	static bool IsMouseUp();
	// Returns whether a mouse button is held.
	static bool IsMouseHold();
	static Vector2 GetMousePosition();

	// Sets the function which listens to application frame close event.
	static void SetCloseListener(std::function<void()> onCloseButton);

	void Update();

private:
	static Input* I;

	std::function<void()> onCloseButton;

	std::vector<SDL_Keycode> downKeys;
	std::vector<SDL_Keycode> upKeys;
	std::vector<SDL_Keycode> holdKeys;

	std::vector<Uint8> downButtons;
	std::vector<Uint8> upButtons;
	std::vector<Uint8> holdButtons;

	Uint8 downHats;
	Uint8 upHats;
	Uint8 holdHats;

	SDL_Joystick* joyStick;
	Vector2 mousePos;
	int mouseStateFlag;

	Input();
	~Input();

	static bool ContainsKey(std::vector<SDL_Keycode>* container, SDL_Keycode code);
	static bool ContainsButton(std::vector<Uint8>* container, Uint8 code);
	static bool ContainsHat(Uint8* container, Uint8 code);

	void ReleaseKey(std::vector<SDL_Keycode>* container, SDL_Keycode code);
	void ReleaseButton(std::vector<Uint8>* container, Uint8 code);
	void ReleaseHat(Uint8* container, Uint8 code);

	bool AssignKey(std::vector<SDL_Keycode>* container, SDL_Keycode code);
	bool AssignButton(std::vector<Uint8>* container, Uint8 code);
	bool AssignHat(Uint8* container, Uint8 code);
};

#endif