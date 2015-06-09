#pragma once
#include <d2d1.h>
#include <string>
#include "SpriteFlipMode.h"
#include "SpriteInterpolationMode.h"

namespace P2DE
{
	namespace GFX
	{
		/// <summary>	A base image properties. </summary>
		///
		/// <remarks>	Tobias, 09.06.2015. </remarks>
		class BaseImageProperties
		{
			public:
			std::wstring m_SpritesheetName;
			D2D1_POINT_2F m_Position;
			D2D1_POINT_2F m_Scale;
			D2D1_COLOR_F m_Color;
			float m_RotateDegree;
			bool m_RotateFromCenter;
			D2D1_POINT_2F m_RotatePoint;
			SPRITE_FLIP_MODE m_FlipMode;
			SPRITE_INTERPOLATION_MODE m_InterpolationMode;

			BaseImageProperties();
			virtual ~BaseImageProperties(){};
		};

		/// <summary>	Image Properties using an SourceImageRect, inheriting from BaseImageProperties. </summary>
		///
		/// <remarks>	Tobias, 09.06.2015. </remarks>
		class ImagePropertiesR : public BaseImageProperties
		{
			public:
			D2D1_RECT_F m_SourceImageRect;

			ImagePropertiesR();
			ImagePropertiesR(
				std::wstring spritesheetName,
				D2D1_POINT_2F position,
				D2D1_RECT_F sourceImageRect,
				D2D1_POINT_2F scale,
				D2D1::ColorF color,
				float rotateDegree,
				bool rotateFromCenter,
				D2D1_POINT_2F rotatePoint,
				SPRITE_FLIP_MODE flipMode,
				SPRITE_INTERPOLATION_MODE interpolationMode);
		};

		/// <summary>	Image Properties using an SourceFrameIdx, inheriting from BaseImageProperties. </summary>
		///
		/// <remarks>	Tobias, 09.06.2015. </remarks>
		class ImagePropertiesI : public BaseImageProperties
		{
			public:
			unsigned int m_SourceFrameIdx;

			ImagePropertiesI();
			ImagePropertiesI(
				std::wstring spritesheetName,
				D2D1_POINT_2F position,
				unsigned int sourceFrameIdx,
				D2D1_POINT_2F scale,
				D2D1::ColorF color,
				float rotateDegree,
				bool rotateFromCenter,
				D2D1_POINT_2F rotatePoint,
				SPRITE_FLIP_MODE flipMode,
				SPRITE_INTERPOLATION_MODE interpolationMode);
		};
	}
}