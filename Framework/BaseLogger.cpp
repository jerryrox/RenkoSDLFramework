#include "BaseLogger.h"

#include "StringUtils.h"

BaseLogger::BaseLogger() {}

BaseLogger::~BaseLogger()
{
	buffer.clear();
}

BaseLogger& BaseLogger::PutLine() { buffer.append("\n"); return *this; };

BaseLogger& BaseLogger::Put(std::wstring str) { buffer.append(StringUtils::WStringToString(str)); return *this; }

BaseLogger& BaseLogger::Put(std::string str) { buffer.append(str); return *this; }

BaseLogger& BaseLogger::Put(int i) { buffer.append(std::to_string(i)); return *this; }

BaseLogger& BaseLogger::Put(float f) { buffer.append(std::to_string(f)); return *this; }

BaseLogger& BaseLogger::Put(double d) { buffer.append(std::to_string(d)); return *this; }

void BaseLogger::Print(std::string str) { Put(str).Print(); };