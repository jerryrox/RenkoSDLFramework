#pragma once

#ifdef _DEBUG
#ifndef _TESTCODE_BASE_
#define _TESTCODE_BASE_

#include <functional>

class TestCodeBase
{
public:
	virtual ~TestCodeBase();

	virtual void Entry() = 0;

	// Simulates game loop.
	void SimulateUpdate(double fps, std::function<bool(float)> callback);
};

#endif
#endif