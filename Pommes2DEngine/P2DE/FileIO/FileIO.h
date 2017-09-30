#pragma once
#include <vector>
#include <string>
#include "../Common.h"

namespace P2DE
{
	namespace FILEIO
	{
		class P2DE_DECLSPEC FileIO
		{
			public:
			static bool ReadBinaryFile(std::wstring filePath, std::vector<unsigned char>* outputData);
			static bool SaveBinaryFile(std::wstring filePath, std::vector<unsigned char>* inputData);
			static std::vector<char> ReadToByteArray(char * filename);
		};
	}
}

