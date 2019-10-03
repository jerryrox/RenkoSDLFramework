#pragma once

#ifndef _DEBUG_MODULE_
#define _DEBUG_MODULE_

#include "BaseLogger.h"

class BaseLogger;

class Debug
{
public:
	static void Initialize(BaseLogger* logger);
	static void Destroy();
	static BaseLogger* Log();

private:
	static BaseLogger* Logger;
};

#endif