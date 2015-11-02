#pragma once
#include <vector>

struct VERTEX
{
	float X, Y, Z;      // position
	P2DE_COLOR4 Color;    // color
};

struct SGeometry
{
	std::vector<VERTEX> m_Vertices;
	std::vector<uint32_t> m_Indices;
};