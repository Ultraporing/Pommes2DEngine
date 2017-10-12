#pragma once
#include <string>

namespace P2DE
{
	namespace UTILITIES
	{
		std::wstring StringToWString(const std::string& s);
		std::string WStringToString(const std::wstring& s);
	}
}