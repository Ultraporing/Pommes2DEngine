#include "FileIO.h"
#include <iterator>
#include <fstream>

using namespace P2DE::FILEIO;

bool FileIO::ReadBinaryFile(std::wstring filePath, std::vector<unsigned char>* outputData)
{
	std::ifstream file = std::ifstream(filePath, std::ifstream::in | std::ifstream::binary);
	file.unsetf(std::ios::skipws);
	if (!file.is_open())
	{
		outputData = NULL;
		return false;
	}

	// get file length
	file.seekg(0, file.end);
	std::streampos fileLength = file.tellg();
	file.seekg(0, file.beg);

	std::vector<unsigned char> buffer = std::vector<unsigned char>((unsigned int)fileLength);
	buffer.insert(buffer.begin(),
		std::istream_iterator<unsigned char>(file),
		std::istream_iterator<unsigned char>());

	*outputData = buffer;

	file.close();
		
	return true;
}

bool FileIO::SaveBinaryFile(std::wstring filePath, std::vector<unsigned char>* inputData)
{
	std::ofstream file = std::ofstream(filePath, std::ofstream::out | std::ofstream::binary);
	file.unsetf(std::ostream::skipws);
	if (!file.is_open())
	{
		return false;
	}

	file.write((const char*)inputData->data(), inputData->size()*sizeof(unsigned char));

	file.close();

	return true;
}

std::vector<char> FileIO::ReadToByteArray(char* filename)
{
	std::vector<char> data;
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	data.resize((const unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&data[0], data.size());
	return data;
}
