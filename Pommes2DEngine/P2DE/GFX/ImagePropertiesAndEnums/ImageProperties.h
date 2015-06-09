#pragma once
#include <d2d1.h>
#include <string>
#include "SpriteFlipMode.h"
#include "SpriteInterpolationMode.h"

namespace P2DE
{
	namespace GFX
	{
		struct BaseImageProperties
		{
			std::wstring m_SpritesheetName;
			D2D1_POINT_2F m_Position;
			D2D1_POINT_2F m_Scale;
			D2D1::ColorF m_Color;
			float m_RotateDegree;
			bool m_RotateFromCenter;
			D2D1_POINT_2F m_RotatePoint;
			SPRITE_FLIP_MODE m_FlipMode;
			SPRITE_INTERPOLATION_MODE m_InterpolationMode;
		};

		struct ImagePropertiesR : public BaseImageProperties
		{
			D2D1_RECT_F m_SourceImageRect;
		};

		struct ImagePropertiesI : public BaseImageProperties
		{
			unsigned int m_SourceFrameIdx;
		};
	}
}