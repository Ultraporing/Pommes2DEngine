#include "Spritesheet.h"
#include <P2DE\GFX\Graphics.h>
#include <fstream>
#include <vector>

namespace FTGame
{
	namespace GFX
	{
		Spritesheet::Spritesheet()
		{
			m_SpritesheetBitmap = NULL;
			m_SpritesheetInfo = SpritesheetInfo();
			m_SpritesheetInfo.m_Margin = 0;
			m_SpritesheetInfo.m_Name = L"";
			m_SpritesheetInfo.m_DirPath = L"";
			m_SpritesheetInfo.m_TileWidth = 0;
			m_SpritesheetInfo.m_TileHeight = 0;
			m_SpritesheetInfo.m_NumXframes = 0;
			m_SpritesheetInfo.m_NumYframes = 0;
		}

		Spritesheet::~Spritesheet()
		{
			UnloadSpritesheetBitmap();
			m_SpritesheetInfo = SpritesheetInfo();
		}

		bool Spritesheet::LoadSpritesheet(const std::wstring& pathToSpritesheetInfoTXT, P2DE::GFX::Graphics* graphics)
		{
			if (m_SpritesheetInfo.m_Name.compare(L"") != 0)
				return ReloadSpritesheetBitmap(graphics);
			
			std::wifstream infoFile(pathToSpritesheetInfoTXT);
			std::wstring line;

			while (std::getline(infoFile, line))
			{
				if (line.find(L"#") == std::wstring::npos)
					continue;

				if (line.find(L"#NAME=") != std::wstring::npos)
				{
					m_SpritesheetInfo.m_Name = line.substr(6);
					continue;
				}
				if (line.find(L"#TILE_SIZE_W=") != std::wstring::npos)
				{
					m_SpritesheetInfo.m_TileWidth = _wtoi(line.substr(13).c_str());
					continue;
				}
				if (line.find(L"#TILE_SIZE_H=") != std::wstring::npos)
				{
					m_SpritesheetInfo.m_TileHeight = _wtoi(line.substr(13).c_str());
					continue;
				}
				if (line.find(L"#MARGIN=") != std::wstring::npos)
				{
					m_SpritesheetInfo.m_Margin = _wtoi(line.substr(8).c_str());
					continue;
				}
			}
			
			m_SpritesheetInfo.m_DirPath = pathToSpritesheetInfoTXT.substr(0, pathToSpritesheetInfoTXT.find_last_of(L"/\\"));

			if (!graphics->LoadBitmapFromFile(m_SpritesheetInfo.GetFullRelativeBitmapPath().c_str(), &m_SpritesheetBitmap))
				return false;

			m_SpritesheetInfo.m_NumXframes = (int)ceil(m_SpritesheetBitmap->GetSize().width / (m_SpritesheetInfo.m_TileWidth + m_SpritesheetInfo.m_Margin));
			m_SpritesheetInfo.m_NumYframes = (int)ceil(m_SpritesheetBitmap->GetSize().height / (m_SpritesheetInfo.m_TileHeight + m_SpritesheetInfo.m_Margin));

			return true;
		}

		bool Spritesheet::ReloadSpritesheetBitmap(P2DE::GFX::Graphics* graphics)
		{
			if (!m_SpritesheetBitmap)
			{
				return graphics->LoadBitmapFromFile(m_SpritesheetInfo.GetFullRelativeBitmapPath().c_str(), &m_SpritesheetBitmap);
			}

			return false;
		}

		void Spritesheet::DrawFrame(int dstX, int dstY, unsigned int frameId, P2DE::GFX::Graphics* graphics, float scale, float opacity, bool interpolationLinear)
		{
			D2D1_RECT_F drawRec;
			drawRec.left = (frameId % m_SpritesheetInfo.m_NumXframes) * (m_SpritesheetInfo.m_TileWidth + m_SpritesheetInfo.m_Margin);
			drawRec.top = floor(frameId / m_SpritesheetInfo.m_NumXframes) * (m_SpritesheetInfo.m_TileHeight + m_SpritesheetInfo.m_Margin);
			drawRec.right = drawRec.left + m_SpritesheetInfo.m_TileWidth;
			drawRec.bottom = drawRec.top + m_SpritesheetInfo.m_TileHeight;

			graphics->DrawBitmap(m_SpritesheetBitmap, D2D1::RectF(dstX, dstY, dstX + (m_SpritesheetInfo.m_TileWidth * scale), dstY + (m_SpritesheetInfo.m_TileHeight * scale)), drawRec, opacity, interpolationLinear ? D2D1_BITMAP_INTERPOLATION_MODE_LINEAR : D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
		}

		bool Spritesheet::UnloadSpritesheetBitmap()
		{
			if (m_SpritesheetBitmap)
			{
				m_SpritesheetBitmap->Release();
				m_SpritesheetBitmap = NULL;

				return true;
			}

			return false;
		}
	}
}
