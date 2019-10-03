#pragma once

#ifndef _CONSOLE_LOGGER_
#define _CONSOLE_LOGGER_

#include "BaseLogger.h"

class ConsoleLogger :
	public BaseLogger
{
public:
	ConsoleLogger();
	~ConsoleLogger();

	void Print() override;
};

#endif