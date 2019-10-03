#include "StringUtils.h"

#include <algorithm> 
#include <cctype>
#include <locale>
#include <string>
#include <iomanip>
#include <sstream>

std::string StringUtils::WStringToString(std::wstring wstr)
{
	std::string s;
	s.assign(wstr.begin(), wstr.end());
	return s;
}
std::wstring StringUtils::StringToWstring(std::string str)
{
	std::wstring ws;
	ws.assign(str.begin(), str.end());
	return ws;
}

// https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
void StringUtils::Trim(std::string& str)
{
	TrimStart(str);
	TrimEnd(str);
}
inline void StringUtils::TrimStart(std::string& str)
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}
inline void StringUtils::TrimEnd(std::string& str)
{
	str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), str.end());
}

std::string StringUtils::ToPercent(float value, int precision)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << value*100.0f << "%";
	return stream.str();
}
std::string StringUtils::ToPercent(double value, int precision)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << value*100.0 << "%";
	return stream.str();
}

std::string StringUtils::SubStringFromLastChar(std::string str, char ch, int count)
{
	for (int i = (int)str.size() - 1; i >= 0; i--)
	{
		if (str.at(i) == ch)
		{
			count--;
			if (count <= 0)
				return str.substr(i+1);
		}
	}
	return str;
}

std::wstring StringUtils::SubStringFromLastChar(std::wstring str, wchar_t ch, int count)
{
	for (int i = (int)str.size() - 1; i >= 0; i--)
	{
		if (str.at(i) == ch)
		{
			count--;
			if (count <= 0)
				return str.substr(i + 1);
		}
	}
	return str;
}