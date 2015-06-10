#pragma once
#include <d2d1.h>
#include <string>
#include "SpriteFlipMode.h"
#include "SpriteInterpolationMode.h"
#include "../../FileIO/SerializeableData.h"

// Align Data to Byte boundaries, needed because of file reading
#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(1)

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
		class ImagePropertiesR : public BaseImageProperties, public P2DE::FILEIO::SerializeableData
		{
			public:
			D2D1_RECT_F m_SourceImageRect;

			ImagePropertiesR();
			ImagePropertiesR(
				std::wstring spritesheetName,
				D2D1_RECT_F sourceImageRect,
				D2D1_POINT_2F scale,
				D2D1::ColorF color,
				float rotateDegree,
				bool rotateFromCenter,
				D2D1_POINT_2F rotatePoint,
				SPRITE_FLIP_MODE flipMode,
				SPRITE_INTERPOLATION_MODE interpolationMode);

			void WriteToBinary(std::vector<byte>* outputData) override;
			static ImagePropertiesR ReadFromBinary(std::vector<byte>* inputData);
		};

		/// <summary>	Image Properties using an SourceFrameIdx, inheriting from BaseImageProperties. </summary>
		///
		/// <remarks>	Tobias, 09.06.2015. </remarks>
		class ImagePropertiesI : public BaseImageProperties, public P2DE::FILEIO::SerializeableData
		{
			public:
			unsigned int m_SourceFrameIdx;

			ImagePropertiesI();
			ImagePropertiesI(
				std::wstring spritesheetName,
				unsigned int sourceFrameIdx,
				D2D1_POINT_2F scale,
				D2D1::ColorF color,
				float rotateDegree,
				bool rotateFromCenter,
				D2D1_POINT_2F rotatePoint,
				SPRITE_FLIP_MODE flipMode,
				SPRITE_INTERPOLATION_MODE interpolationMode);

			void WriteToBinary(std::vector<byte>* outputData) override;
			static ImagePropertiesI ReadFromBinary(std::vector<byte>* inputData);
		};
	}
}

#ifdef WIN32
#pragma pack(pop)
#endif
#ifdef LINUX
#pragma pack()
#endif