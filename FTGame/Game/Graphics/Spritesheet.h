#pragma once
#include <string>

struct ID2D1Bitmap;
namespace P2DE
{
	namespace GFX
	{
		class Graphics;
	}
}

namespace FTGame
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
			public:
			SpritesheetInfo m_SpritesheetInfo;
			ID2D1Bitmap* m_SpritesheetBitmap;

			Spritesheet();
			~Spritesheet();

			bool LoadSpritesheet(const std::wstring& pathToSpritesheetInfoTXT, P2DE::GFX::Graphics* graphics);
			bool UnloadSpritesheetBitmap();

			void DrawFrame(int dstX, int dstY, unsigned int frameId, P2DE::GFX::Graphics* graphics, float scale = 1.0f, float opacity = 1.0f, bool interpolationLinear = true);

			private:
			bool ReloadSpritesheetBitmap(P2DE::GFX::Graphics* graphics);
		};
	}
}

