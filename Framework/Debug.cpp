#include "Debug.h"

BaseLogger* Debug::Logger = 0;

void Debug::Initialize(BaseLogger* logger)
{
	if (Logger != 0)
		Destroy();
	Logger = logger;
}

void Debug::Destroy()
{
	if(Logger != 0)
		delete Logger;
	Logger = 0;
}

BaseLogger* Debug::Log()
{
	if (Logger == 0)
		return 0;
	return Logger;
}