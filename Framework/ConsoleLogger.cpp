#include "ConsoleLogger.h"

#include <Windows.h>

ConsoleLogger::ConsoleLogger()
{
}

ConsoleLogger::~ConsoleLogger()
{
}

void ConsoleLogger::Print()
{
	buffer.append("\n");
	OutputDebugStringA(buffer.c_str());
	buffer.clear();
}