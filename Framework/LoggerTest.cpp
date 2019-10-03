#ifdef _DEBUG

#include "LoggerTest.h"

#include "ConsoleLogger.h"
#include "Debug.h"

void LoggerTest::Entry()
{
	TestConsoleLogger();
	TestStaticConsoleLogger();
}

void LoggerTest::TestConsoleLogger()
{
	ConsoleLogger logger;
	logger.Put("Testing console logger: ").Put(1).Put(" ").Put(2.5f).Put(" ").Put(3.0).Print();
}

void LoggerTest::TestStaticConsoleLogger()
{
	Debug::Log()->Put("Testing static console logger").Print();
}

#endif