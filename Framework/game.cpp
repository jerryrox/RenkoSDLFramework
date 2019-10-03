#include "game.h"

#include "RenkoFramework.h"
#include "Input.h"
#include "Scene.h"

Game* Game::I = 0;
std::string Game::Version = "0.0.0";

Game::Game() :
	scene(0),
	isQuitting(false)
{
	scene = new Scene();

	RenkoFramework::Initialize(60);
	RenkoFramework::GetInstance()->SetRootObject(scene);
	Input::SetCloseListener(std::bind(&Game::Quit, this));
}

Game::~Game()
{
	RenkoFramework::Destroy();
}

Game* Game::GetInstance()
{
	if (I == 0)
		Debug::Log()->Put("Game::GetInstance - Not initialized!").Print();
	return I;
}

bool Game::Initialize()
{
	if (I != 0)
	{
		Debug::Log()->Put("Game::Initialize - Already initialized!").Print();
		return false;
	}
	I = new Game();
	return true;
}

void Game::Destroy()
{
	if (I != 0)
		delete I;
	I = 0;
}

void Game::PostInitialize()
{
	// Awake scene
	scene->Init();

	// Start framework.
	RenkoFramework::GetInstance()->Start();
}

void Game::Quit()
{
	if (isQuitting)
		return;
	isQuitting = true;

	// TODO: Gracefully quit if required.
	ForceQuit();
}

void Game::ForceQuit()
{
	RenkoFramework::GetInstance()->Shutdown();
}