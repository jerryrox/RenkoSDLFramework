#include "Events.h"

void Events::Invoke()
{
	for (int i = 0; i < (int)functions.size(); i++)
	{
		auto func = functions.at(i);
		if (func == nullptr)
		{
			functions.erase(functions.begin() + i);
			continue;
		}
		func();
	}
}

void Events::Clear() { functions.clear(); }

Events& Events::operator+=(std::function<void()> f) { functions.push_back(f); return *this; }