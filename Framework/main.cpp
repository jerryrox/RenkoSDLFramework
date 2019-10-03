// COMP710 GP 2D Framework 2019

#include <SDL.h>
#include <crtdbg.h>

#define TestMode true && _DEBUG
#if TestMode

// Debugging is automatically initialized.
#include "Debug.h"
#include "ConsoleLogger.h"

#include "AnimeTest.h"
#include "EventsTest.h"
#include "LoggerTest.h"
#include "FrameworkTest.h"

void PerformTest()
{
	Debug::Initialize(new ConsoleLogger());

	// Instantiate test code instances here.
	TestCodeBase* testCode = new FrameworkTest();
	if (testCode != 0)
	{
		testCode->Entry();
		delete testCode;
	}

	Debug::Destroy();
}

#else

#include "game.h"

#endif

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#if TestMode
	PerformTest();
#else
	// If game initialized, start the game.
	if (Game::Initialize())
	{
		// The game would've been quit if this statement ends.
		Game::GetInstance()->PostInitialize();
	}
	Game::Destroy();
#endif

	return (0);
}