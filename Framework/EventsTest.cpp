#ifdef _DEBUG

#include "EventsTest.h"

#include "Debug.h"
#include "Events.h"

void EventsTest::Entry()
{
	Events events;

	events += std::bind(&EventsTest::TestEvent, this);
	events += []() { Debug::Log()->Put("Called A").Print(); };

	events.Invoke();
	events.Clear();
	events.Invoke();
}

void EventsTest::TestEvent()
{
	Debug::Log()->Put("Called TestEvent").Print();
}

#endif