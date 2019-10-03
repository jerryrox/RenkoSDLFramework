#pragma once

#ifndef _STRING_UTILS_
#define _STRING_UTILS_

#include <string>

class StringUtils
{
public:
	static std::string WStringToString(std::wstring wstr);
	static std::wstring StringToWstring(std::string str);

	static void Trim(std::string& str);
	static void TrimStart(std::string& str);
	static void TrimEnd(std::string& str);

	static std::string ToPercent(float value, int precision);
	static std::string ToPercent(double value, int precision);

	static std::string SubStringFromLastChar(std::string str, char ch, int count = 1);
	static std::wstring SubStringFromLastChar(std::wstring str, wchar_t ch, int count = 1);
};

#endif