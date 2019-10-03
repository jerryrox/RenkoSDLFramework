#include "Input.h"

#include "Debug.h"

#include <algorithm>

Input* Input::I = 0;

Input::Input() :
	joyStick(0),
	mousePos(0, 0),
	mouseStateFlag(0),
	downHats(0),
	holdHats(0),
	upHats(0)
{
}

Input::~Input()
{
	//if (joyStick != 0)
	//	SDL_GameControllerClose(joyStick);
	joyStick = 0;
}

bool Input::Initialize()
{
	if (I != 0)
	{
		Debug::Log()->Put("Input is already initialized!").Print();
		return false;
	}
	I = new Input();

	// Init joystick if applicable
	I->joyStick = SDL_JoystickOpen(0);
	if (I->joyStick == 0)
		Debug::Log()->Put("Controller not found.").Print();
	else
		Debug::Log()->Put("Controller initialized.").Print();

	return true;
}

void Input::Destroy()
{
	if (I != 0)
		delete I;
	I = 0;
}

Input* Input::GetInstance()
{
	if (I == 0)
		Debug::Log()->Put("Input is not initialized!").Print();
	return I;
}

bool Input::IsKeyDown(SDL_Keycode code) { return ContainsKey(&(I->downKeys), code); }
bool Input::IsButtonDown(Uint8 code) { return ContainsButton(&(I->downButtons), code); }
bool Input::IsHatDown(Uint8 code) { return ContainsHat(&(I->downHats), code); }

bool Input::IsKeyUp(SDL_Keycode code) { return ContainsKey(&(I->upKeys), code); }
bool Input::IsButtonUp(Uint8 code) { return ContainsButton(&(I->upButtons), code); }
bool Input::IsHatUp(Uint8 code) { return ContainsHat(&(I->upHats), code); }

bool Input::IsKeyHold(SDL_Keycode code) { return ContainsKey(&(I->holdKeys), code); }
bool Input::IsButtonHold(Uint8 code) { return ContainsButton(&(I->holdButtons), code); }
bool Input::IsHatHold(Uint8 code) { return ContainsHat(&(I->holdHats), code); }

bool Input::IsAnyKeyDown() { return I->downKeys.size() > 0; }
bool Input::IsAnyButtonDown() { return I->downButtons.size() > 0; }
bool Input::IsAnyHatDown() { return I->downHats > 0; }

bool Input::IsAnyKeyUp() { return I->upKeys.size() > 0; }
bool Input::IsAnyButtonUp() { return I->upButtons.size() > 0; }
bool Input::IsAnyHatUp() { return I->upHats > 0; }

bool Input::IsAnyKeyHold() { return I->holdKeys.size() > 0; }
bool Input::IsAnyButtonHold() { return I->holdButtons.size() > 0; }
bool Input::IsAnyHatHold() { return I->holdHats > 0; }

bool Input::IsMouseDown() { return I->mouseStateFlag == 1; }
bool Input::IsMouseUp() { return I->mouseStateFlag == 3; }
bool Input::IsMouseHold() { return I->mouseStateFlag == 1 || I->mouseStateFlag == 2; }

Vector2 Input::GetMousePosition() { return I->mousePos; }

void Input::SetCloseListener(std::function<void()> onCloseButton)
{
	if(I != 0)
		I->onCloseButton = onCloseButton;
}

void Input::Update()
{
	// Free all temporary state keys.
	downKeys.clear();
	downButtons.clear();
	downHats = 0;
	upKeys.clear();
	upButtons.clear();
	upHats = 0;

	// Update mouse state
	if (mouseStateFlag == 1)
		mouseStateFlag = 2;
	else if(mouseStateFlag == 3)
		mouseStateFlag = 0;

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		// Quitting game
		if (event.type == SDL_QUIT)
		{
			if (onCloseButton != 0)
				onCloseButton();
		}
		// Detect key down
		else if (event.type == SDL_KEYDOWN)
		{
			SDL_Keycode key = event.key.keysym.sym;
			// Flag this key code as "down" and "hold" only if not already done.
			if (AssignKey(&holdKeys, key))
				AssignKey(&downKeys, key);
		}
		// Detect key up
		else if (event.type == SDL_KEYUP)
		{
			SDL_Keycode key = event.key.keysym.sym;
			// Find and remove key from down and hold containers.
			ReleaseKey(&downKeys, key);
			ReleaseKey(&holdKeys, key);
			// Flag this key code as "up".
			AssignKey(&upKeys, key);
		}
		// Detect hat input.
		else if (event.type == SDL_JOYHATMOTION)
		{
			Uint8 curValue = event.jhat.value;
			for (Uint8 hat = 1; hat < 9; hat *= 2)
			{
				// Hat is currently down.
				if (curValue & hat)
				{
					// Detect press down.
					if (AssignHat(&holdHats, hat))
					{
						AssignHat(&downHats, hat);
					}
				}
				// Hat is currently not down.
				else
				{
					// If was holding
					if (ContainsHat(&holdHats, hat))
					{
						// Release pressing states.
						ReleaseHat(&downHats, hat);
						ReleaseHat(&holdHats, hat);
						// Set release state.
						AssignHat(&upHats, hat);
					}
				}
			}
		}
		// Detect controller down
		else if (event.type == SDL_JOYBUTTONDOWN)
		{
			Uint8 button = event.jbutton.button;
			//Debug::Log()->Put("Down button: ").Put(button).Print();
			// Flag this button code as "down" and "hold" only if not already done.
			if (AssignButton(&holdButtons, button))
				AssignButton(&downButtons, button);
		}
		// Detect controller up
		else if (event.type == SDL_JOYBUTTONUP)
		{
			Uint8 button = event.jbutton.button;
			//Debug::Log()->Put("Up button: ").Put(button).Print();
			// Find and remove button from down and hold containers.
			ReleaseButton(&downButtons, button);
			ReleaseButton(&holdButtons, button);
			// Flag this button code as "up".
			AssignButton(&upButtons, button);
		}
		// Mouse button down
		else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{
			mouseStateFlag = 1;
		}
		// Mouse button up
		else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
		{
			mouseStateFlag = 3;
		}
	}

	// Get the last mouse position
	int mouseX, mouseY;
	int mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	mousePos.x = (float)mouseX;
	mousePos.y = (float)mouseY;
}

bool Input::ContainsKey(std::vector<SDL_Keycode>* container, SDL_Keycode code)
{
	for (int i = 0; i < (int)container->size(); i++)
	{
		if (container->at(i) == code)
			return true;
	}
	return false;
}
bool Input::ContainsButton(std::vector<Uint8>* container, Uint8 code)
{
	for (int i = 0; i < (int)container->size(); i++)
	{
		if (container->at(i) == code)
			return true;
	}
	return false;
}
bool Input::ContainsHat(Uint8* container, Uint8 code)
{
	return (*container & code) > 0;
}

void Input::ReleaseKey(std::vector<SDL_Keycode>* container, SDL_Keycode code)
{
	for (int i=(int)container->size()-1; i>=0; i--)
	{
		if (container->at(i) == code)
			container->erase(container->begin() + i);
	}
}
void Input::ReleaseButton(std::vector<Uint8>* container, Uint8 code)
{
	for (int i = (int)container->size() - 1; i >= 0; i--)
	{
		if (container->at(i) == code)
			container->erase(container->begin() + i);
	}
}
void Input::ReleaseHat(Uint8* container, Uint8 code)
{
	if (*container & code)
		*container -= code;
}

bool Input::AssignKey(std::vector<SDL_Keycode>* container, SDL_Keycode code)
{
	if (ContainsKey(container, code))
		return false;
	container->push_back(code);
	return true;
}
bool Input::AssignButton(std::vector<Uint8>* container, Uint8 code)
{
	if (ContainsButton(container, code))
		return false;
	container->push_back(code);
	return true;
}
bool Input::AssignHat(Uint8* container, Uint8 code)
{
	if (ContainsHat(container, code))
		return false;
	*container |= code;
	return true;
}