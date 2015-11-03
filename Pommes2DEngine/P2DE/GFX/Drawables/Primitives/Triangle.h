#pragma once
#include "..\BaseDrawable.h"

namespace P2DE
{
	namespace GFX
	{
		namespace DRAWABLES
		{
			namespace PRIMITIVES
			{
				class Triangle : public P2DE::GFX::DRAWABLES::BaseDrawable
				{
					public:
					virtual void Load() override;
					virtual void Unload() override;
					virtual void Draw() override;
				};
			}
		}
	}
}

