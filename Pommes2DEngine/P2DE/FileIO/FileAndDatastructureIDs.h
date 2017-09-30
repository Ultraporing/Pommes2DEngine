#pragma once
#include "../Common.h"

typedef unsigned int P2DE_DECLSPEC DatastructureID;

enum class P2DE_DECLSPEC FileIDs : DatastructureID
{

};

enum class P2DE_DECLSPEC DatastructureIDs : DatastructureID
{
	ImageProperties_START = 44198,
	ImageProperties_END = 44199,
	ImagePropertiesVector_START = 44200,
	ImagePropertiesVector_END = 44201
};