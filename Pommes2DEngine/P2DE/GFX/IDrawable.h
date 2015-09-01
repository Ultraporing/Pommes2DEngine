#pragma once
#include "D3D11Common.h"
#include "SGeometry.h"

struct P2DE_Shader;

interface IDrawable
{
	public:
		P2DE_VEC3F m_Pos;
		P2DE_COLOR4 m_TintColor;
		SGeometry m_Geometry;
		P2DE_Shader* m_Shader;
};

