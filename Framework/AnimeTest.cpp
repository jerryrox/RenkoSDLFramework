#ifdef _DEBUG

#include "AnimeTest.h"

#include "Anime.h"
#include "Easing.h"
#include "EaseType.h"
#include "Debug.h"
#include "ConsoleLogger.h"

using namespace std;

void AnimeTest::Entry()
{
	Easing::Initialize();

	TestEasing();
	TestAnime();

	Easing::Destroy();
}

void AnimeTest::TestEasing()
{
	for (int i = 0; i < EaseType::END; i++)
	{
		Debug::Log()->Put("Type: ").Put(i).Put(" | 0: ").Put(Easing::Ease((EaseType)i, 0, 0, 1, 1)).Put(" | 0.5: ").Put(Easing::Ease((EaseType)i, 0.5, 0, 1, 1)).Put(" | 0.5: ").Put(Easing::Ease((EaseType)i, 1, 0, 1, 1)).Print();
	}
}

void AnimeTest::TestAnime()
{
	Anime anime(1);
	anime.SetWrapMode(Wrap_Loop);
	anime.SetStopMode(Stop_Reset);
	anime.AddEvent(0, []() {
		Debug::Log()->Put("Event at frame 0").Print();
	});
	anime.AddEvent(1, []() {
		Debug::Log()->Put("Event at frame 1").Print();
	});
	anime.AddEvent(2, []() {
		Debug::Log()->Put("Event at frame 2").Print();
	});
	anime.AddSection(0, 5, EaseType::CubicEaseOut, [](float progress) {
		Debug::Log()->Put("Progress: ").Put(progress).Print();
	});
	anime.Play();

	/*for (int i = 0; i < 10; i++)
		anime.Update(1);*/

	int a = 0;
	SimulateUpdate(2, [&](float deltaTime) {
		a++;
		if (anime.IsPlaying())
		{
			if (a >= 10)
			{
				Debug::Log()->Put("----- Stopped -----").Print();
				anime.Stop();
				a = 0;
			}
		}
		else
		{
			if (a >= 3)
			{
				Debug::Log()->Put("----- Playing -----").Print();
				anime.Play();
				a = 0;
			}
		}
		anime.Update(deltaTime);
		return true;
	});
}

#endif