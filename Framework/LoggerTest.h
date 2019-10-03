#pragma once

#ifdef _DEBUG
#ifndef _LOGGER_TEST_
#define _LOGGER_TEST_

#include "TestCodeBase.h"

class LoggerTest :
	public TestCodeBase
{
public:
	void Entry() override;

private:
	void TestConsoleLogger();
	void TestStaticConsoleLogger();
};

#endif
#endif