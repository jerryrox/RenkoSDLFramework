#pragma once

#ifndef _BASE_LOGGER_
#define _BASE_LOGGER_

#include <string>

class BaseLogger
{
public:
	BaseLogger();
	~BaseLogger();

	BaseLogger& PutLine();
	BaseLogger& Put(std::wstring str);
	BaseLogger& Put(std::string str);
	BaseLogger& Put(int i);
	BaseLogger& Put(float f);
	BaseLogger& Put(double d);

	void Print(std::string str);

	virtual void Print() = 0;

protected:
	std::string buffer;
};

#endif