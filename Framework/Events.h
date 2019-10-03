#pragma once

#ifndef _EVENTS_
#define _EVENTS_

#include <functional>
#include <vector>

// Class designed to somewhat simulate C# event delegates.
class Events
{
public:
	// Invokes all added events with specified value.
	void Invoke();

	// Clears all registered events.
	void Clear();

	Events& operator+=(std::function<void()> mFunc);
	
private:
	std::vector<std::function<void()>> functions;
};

#endif