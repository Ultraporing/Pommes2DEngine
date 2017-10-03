#pragma once
#include <string>
#include <algorithm>

// Prototype for conversion functions
std::wstring StringToWString(const std::string& s);
std::string WStringToString(const std::wstring& s);

std::wstring StringToWString(const std::string& s)
{
	std::wstring temp(s.length(), L' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}


std::string WStringToString(const std::wstring& s)
{
	std::string temp(s.length(), ' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}