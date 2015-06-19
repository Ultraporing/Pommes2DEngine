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
		/// <summary>	Image Properties using an SourceImageRect, inheriting from BaseImageProperties. </summary>
		///
		/// <remarks>	Tobias, 09.06.2015. </remarks>
		class ImageProperties : public P2DE::FILEIO::SerializeableDataStructure
		{
			public:
			enum ImagePropertiesDiffFlags
			{
				IPDF_SPRITESHEET_NAME = 1 << 0,
				IPDF_SOURCE_FRAME_IDX = 1 << 1,
				IPDF_SOURCE_IMAGE_RECT = 1 << 2,
				IPDF_SCALE = 1 << 3,
				IPDF_COLOR = 1 << 4,
				IPDF_ROTATE_DEGREE = 1 << 5,
				IPDF_ROTATE_FROM_CENTER = 1 << 6,
				IPDF_ROTATE_POINT = 1 << 7,
				IPDF_FLIP_MODE = 1 << 8,
				IPDF_INTERPOLATION_MODE = 1 << 9
			};

			private:
			int m_diffrentToLastFlags;

			public:		
			std::wstring m_SpritesheetName;
			unsigned int m_SourceFrameIdx;
			D2D1_RECT_F m_SourceImageRect;
			D2D1_POINT_2F m_Scale;
			D2D1_COLOR_F m_Color;
			float m_RotateDegree;
			bool m_RotateFromCenter;
			D2D1_POINT_2F m_RotatePoint;
			SPRITE_FLIP_MODE m_FlipMode;
			SPRITE_INTERPOLATION_MODE m_InterpolationMode;

			ImageProperties();
			ImageProperties(
				std::wstring spritesheetName,
				unsigned int sourceFrameIdx,
				D2D1_RECT_F sourceImageRect,
				D2D1_POINT_2F scale,
				D2D1::ColorF color,
				float rotateDegree,
				bool rotateFromCenter,
				D2D1_POINT_2F rotatePoint,
				SPRITE_FLIP_MODE flipMode,
				SPRITE_INTERPOLATION_MODE interpolationMode);

			void InitDatastructureIDs() override;

			bool UsesSourceImageRect() const;
			void SetDiffFlags(ImageProperties* previousImageProperty);

			void WriteToBinary(std::vector<byte>* outputData) override;
			void WriteToBinary(std::vector<byte>* outputData, ImageProperties* previousImageProperty);
			static void WriteMultipleToBinary(std::vector<byte>* outputData, std::vector<ImageProperties>* imagePropertiesVector);
			
			static bool ReadFromBinary(std::vector<byte>* inputData, std::vector<byte>::const_iterator* offset, ImageProperties* previousImageProperty, ImageProperties& readImageProperties);
			static bool ReadMultipleFromBinary(std::vector<byte>* inputData, std::vector<ImageProperties>& readImagePropertiesVector);
		};
	}
}

#ifdef WIN32
#pragma pack(pop)
#endif
#ifdef LINUX
#pragma pack()
#endif