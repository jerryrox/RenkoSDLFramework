#pragma once

#ifndef __GAME_H__
#define __GAME_H__

#include <string>

class RenkoFramework;
class Scene;

class Game
{
public:
	static std::string Version;
	static Game* I;

	static Game* GetInstance();
	static bool Initialize();
	static void Destroy();

	// Handles additional actions after initialization.
	void PostInitialize();

	// Triggers game stop gracefully.
	void Quit();

	// Instantly quits game.
	void ForceQuit();

private:
	Scene* scene;

	bool isQuitting;

	Game();
	~Game();
};

#endif // __GAME_H__
