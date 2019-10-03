#pragma once

#ifndef _PATH_UTILS_
#define _PATH_UTILS_

#include <string>

class PathUtils
{
public:
	// Returns a new string with combined path of x and y.
	static std::string Combine(std::string* x, std::string* y);

	// Returns a new wstring with combined path of x and y.
	static std::wstring Combine(std::wstring* x, std::wstring* y);
};

#endif