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
				class P2DE_DECLSPEC Triangle : public P2DE::GFX::DRAWABLES::BaseDrawable
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

