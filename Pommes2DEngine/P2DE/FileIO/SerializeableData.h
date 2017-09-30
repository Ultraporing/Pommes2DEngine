#pragma once
#include <vector>
#include <assert.h>
#include "FileAndDatastructureIDs.h"

namespace P2DE
{
	namespace FILEIO
	{
		class P2DE_DECLSPEC SerializeableDataStructure
		{
			protected:
			DatastructureID ID_BLOCK_START;
			DatastructureID ID_BLOCK_END;
			
			public:
			virtual void WriteToBinary(std::vector<byte>* outputData) = 0;
			virtual void InitDatastructureIDs() = 0;
		};
	}
}