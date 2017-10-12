#pragma once
#include "..\D3D11Common.h"
#include "SGeometry.h"
#include "..\..\Common.h"

namespace P2DE
{
	namespace GFX
	{
		namespace DRAWABLES
		{
			struct Shader;

			class P2DE_DECLSPEC BaseDrawable
			{
				public:
				virtual void Load() = 0;
				virtual void Unload() = 0;
				virtual void Draw() = 0;

				protected:
				VEC3F m_Pos;
				COLOR4 m_TintColor;
				SGeometry m_Geometry;
				Shader* m_Shader;
			};
		}
	}
}