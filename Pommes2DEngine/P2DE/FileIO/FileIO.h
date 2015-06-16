#pragma once
#include <vector>
#include <string>

namespace P2DE
{
	namespace FILEIO
	{
		class FileIO
		{
			public:
			static bool ReadBinaryFile(std::wstring filePath, std::vector<unsigned char>* outputData);
			static bool SaveBinaryFile(std::wstring filePath, std::vector<unsigned char>* inputData);
		};
	}
}

