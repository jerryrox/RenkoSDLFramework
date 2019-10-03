#pragma once

#ifdef _DEBUG
#ifndef _FRAMEWORK_TEST_
#define _FRAMEWORK_TEST_

#include "TestCodeBase.h"

class GameObject;

class FrameworkTest :
	public TestCodeBase
{
public:
	FrameworkTest();
	~FrameworkTest() override;

	void Entry() override;

private:
	GameObject* root;
};

#endif
#endif