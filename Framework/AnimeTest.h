#pragma once

#ifdef _DEBUG
#ifndef _ANIME_TEST_
#define _ANIME_TEST_

#include "TestCodeBase.h"

class AnimeTest :
	public TestCodeBase
{
public:
	void Entry() override;

private:
	void TestEasing();
	void TestAnime();
};

#endif
#endif