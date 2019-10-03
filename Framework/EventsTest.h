#pragma once

#ifdef _DEBUG
#ifndef _EVENTS_TEST_
#define _EVENTS_TEST_

#include "TestCodeBase.h"

class EventsTest :
	public TestCodeBase
{
public:
	void Entry() override;

private:
	void TestEvent();
};

#endif
#endif