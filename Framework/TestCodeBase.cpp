#ifdef _DEBUG

#include "TestCodeBase.h"

#include <chrono>
#include <conio.h>

TestCodeBase::~TestCodeBase() {}

void TestCodeBase::SimulateUpdate(double fps, std::function<bool(float)> callback)
{
	using namespace std::chrono;
	high_resolution_clock::time_point startTime = high_resolution_clock::now();

	double updateRate = 1000.0 / fps;
	double bufferedTime = 0;
	bool shouldLoop = true;
	do
	{
		high_resolution_clock::time_point curTime = high_resolution_clock::now();
		duration<double, std::milli> span = curTime - startTime;
		bufferedTime += span.count();

		if (bufferedTime > updateRate)
		{
			bufferedTime -= updateRate;
			shouldLoop = callback((float)updateRate * 0.001f);
		}

		// Exit
		if (_kbhit())
		{
			char c = _getch();
			if (c == 'q')
				break;
		}

		startTime = curTime;
	} while (shouldLoop);
}

#endif