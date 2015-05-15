#pragma once
#include "Graphics.h"
#include <string>

struct ID2D1Bitmap;

namespace P2DE
{
	namespace GFX
	{
		struct SpritesheetInfo
		{
			std::wstring m_Name;
			std::wstring m_DirPath;
			std::wstring GetFullRelativeBitmapPath()
			{
				std::wstring str(m_DirPath);
				str.append(L"\\");
				str.append(m_Name);

				return str;
			}

			int m_NumXframes, m_NumYframes;
			int m_TileWidth, m_TileHeight;
			int m_Margin;
		};

		class Spritesheet
		{
			private:
			P2DE::GFX::Graphics* m_Graphics;
			ID2D1Effect* m_ColorMatrixFx;
			ID2D1Effect* m_ScaleFx;
			P2DE::UTILITIES::ComPtr<ID2D1Image> m_IntermediateOutputImage;
			SpritesheetInfo m_SpritesheetInfo;
			ID2D1Bitmap* m_SpritesheetBitmap;

			public:
			Spritesheet();
			~Spritesheet();

			SpritesheetInfo GetSpritesheetInfo() { return m_SpritesheetInfo; };
			ID2D1Bitmap* GetSpritesheetBitmap() { return m_SpritesheetBitmap; };

			bool LoadSpritesheet(const std::wstring& pathToSpritesheetInfoTXT, P2DE::GFX::Graphics* graphics);
			bool UnloadSpritesheetBitmap();

			void DrawFrame(D2D1_POINT_2F dest, unsigned int frameId, D2D1_POINT_2F scale = { 1.0f, 1.0f }, D2D1::ColorF color = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), bool interpolationLinear = true);

			private:
			bool ReloadSpritesheetBitmap();
		};
	}
}

