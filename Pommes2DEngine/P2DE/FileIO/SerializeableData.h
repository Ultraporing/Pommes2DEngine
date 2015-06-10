#pragma once
#include <vector>
#include <assert.h>

namespace P2DE
{
	namespace FILEIO
	{
		class SerializeableData
		{
			protected:
			int ID_BLOCK_START;
			int ID_BLOCK_END;
			
			public:
			virtual void WriteToBinary(std::vector<byte>* outputData) = 0;
		};
	}
}