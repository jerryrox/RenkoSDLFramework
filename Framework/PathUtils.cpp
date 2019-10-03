#include "PathUtils.h"

std::string PathUtils::Combine(std::string* x, std::string* y)
{
	if (x == 0 || y == 0)
		return "";
	if (x->size() == 0)
		return std::string(*y);
	if (y->size() == 0)
		return std::string(*x);
	for (int i = (int)x->size() - 1; i >= 0; i--)
	{
		if (x->at(i) != '\\')
			break;
		x->erase(x->begin() + i);
	}
	for (int i=0; i<(int)y->size(); i++)
	{
		if (y->at(i) != '\\')
			break;
		y->erase(y->begin() + i);
	}
	return std::string(*x) + '\\' + std::string(*y);
}

std::wstring PathUtils::Combine(std::wstring* x, std::wstring* y)
{
	if (x == 0 || y == 0)
		return L"";
	if (x->size() == 0)
		return std::wstring(*y);
	if (y->size() == 0)
		return std::wstring(*x);
	for (int i = (int)x->size() - 1; i >= 0; i--)
	{
		if (x->at(i) != L'\\')
			break;
		x->erase(x->begin() + i);
	}
	for (int i = 0; i < (int)y->size(); i++)
	{
		if (y->at(i) != L'\\')
			break;
		y->erase(y->begin() + i);
	}
	return std::wstring(*x) + L'\\' + std::wstring(*y);
}