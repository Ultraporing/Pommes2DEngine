////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	P2DE\GFX\Spritesheet.cpp
//
// summary:	Implements the spritesheet class
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Spritesheet.h"
#include "Graphics.h"
#include <fstream>
#include <vector>

namespace P2DE
{
	namespace GFX
	{
		Spritesheet::Spritesheet()
		{
			m_SpritesheetBitmap = NULL;
			m_Graphics = NULL;
			m_ColorMatrixFx = NULL;
			m_ScaleFx = NULL;
			m_SpritesheetInfo = SpritesheetInfo();
			m_SpritesheetInfo.m_Margin = 0;
			m_SpritesheetInfo.m_FileName = L"";
			m_SpritesheetInfo.m_DirPath = L"";
			m_SpritesheetInfo.m_FrameWidth = 0;
			m_SpritesheetInfo.m_FrameHeight = 0;
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
			std::wstring errorString(L"Failed to load spritesheet: ");
			errorString.append(pathToSpritesheetInfoTXT);

			if (!m_Graphics)
				m_Graphics = graphics;

			if (m_SpritesheetInfo.m_FileName.compare(L"") != 0)
			{
				bool ret = ReloadSpritesheetBitmap();
				if (!ret)
					MessageBox(NULL, errorString.c_str(), L"Spritesheet Loading Error", MB_ICONERROR | MB_OK);

				return ret;
			}
				

			std::wifstream infoFile(pathToSpritesheetInfoTXT);
			std::wstring line;

			while (std::getline(infoFile, line))
			{
				if (line.find(L"#") == std::wstring::npos)
					continue;

				if (line.find(L"#NAME=") != std::wstring::npos)
				{
					m_SpritesheetInfo.m_FileName = line.substr(6);
					continue;
				}
				if (line.find(L"#TILE_SIZE_W=") != std::wstring::npos)
				{
					m_SpritesheetInfo.m_FrameWidth = _wtoi(line.substr(13).c_str());
					continue;
				}
				if (line.find(L"#TILE_SIZE_H=") != std::wstring::npos)
				{
					m_SpritesheetInfo.m_FrameHeight = _wtoi(line.substr(13).c_str());
					continue;
				}
				if (line.find(L"#MARGIN=") != std::wstring::npos)
				{
					m_SpritesheetInfo.m_Margin = _wtoi(line.substr(8).c_str());
					continue;
				}
			}
			
			m_SpritesheetInfo.m_DirPath = pathToSpritesheetInfoTXT.substr(0, pathToSpritesheetInfoTXT.find_last_of(L"/\\"));

			if (!m_Graphics->LoadBitmapFromFile(m_SpritesheetInfo.GetFullRelativeBitmapPath().c_str(), &m_SpritesheetBitmap))
			{
				MessageBox(NULL, errorString.c_str(), L"Spritesheet Loading Error", MB_ICONERROR | MB_OK);
				return false;
			}

			if (!m_Graphics->CreateBitmapScaleEffect(&m_ScaleFx, m_SpritesheetBitmap))
			{
				MessageBox(NULL, errorString.c_str(), L"Spritesheet Loading Error", MB_ICONERROR | MB_OK);
				return false;
			}


			m_ScaleFx->GetOutput(&m_IntermediateOutputImage);
			
			if (!m_Graphics->CreateBitmapTintEffect(&m_ColorMatrixFx, m_IntermediateOutputImage, 1.0f, 1.0f, 1.0f))
			{
				MessageBox(NULL, errorString.c_str(), L"Spritesheet Loading Error", MB_ICONERROR | MB_OK);
				return false;
			}

			m_SpritesheetInfo.m_NumXframes = (int)ceil(m_SpritesheetBitmap->GetSize().width / (m_SpritesheetInfo.m_FrameWidth + m_SpritesheetInfo.m_Margin));
			m_SpritesheetInfo.m_NumYframes = (int)ceil(m_SpritesheetBitmap->GetSize().height / (m_SpritesheetInfo.m_FrameHeight + m_SpritesheetInfo.m_Margin));

			return true;
		}

		bool Spritesheet::UnloadSpritesheetBitmap()
		{
			if (m_SpritesheetBitmap)
			{
				m_SpritesheetBitmap->Release();
				m_SpritesheetBitmap = NULL;
			}

			if (m_IntermediateOutputImage)
			{
				m_IntermediateOutputImage->Release();
				m_IntermediateOutputImage = NULL;
			}

			if (m_ColorMatrixFx)
			{
				m_ColorMatrixFx->Release();
				m_ColorMatrixFx = NULL;
			}

			if (m_ScaleFx)
			{
				m_ScaleFx->Release();
				m_ScaleFx = NULL;
			}

			return true;
		}

		bool Spritesheet::ReloadSpritesheetBitmap()
		{
			if (!m_Graphics->LoadBitmapFromFile(m_SpritesheetInfo.GetFullRelativeBitmapPath().c_str(), &m_SpritesheetBitmap))
				return false;

			if (!m_Graphics->CreateBitmapScaleEffect(&m_ScaleFx, m_SpritesheetBitmap))
				return false;

			m_ScaleFx->GetOutput(&m_IntermediateOutputImage);

			if (!m_Graphics->CreateBitmapTintEffect(&m_ColorMatrixFx, m_IntermediateOutputImage, 1.0f, 1.0f, 1.0f))
				return false;	

			return true;
		}

		void Spritesheet::DrawFrame(D2D1_POINT_2F dest, unsigned int frameId, D2D1_POINT_2F scale, D2D1::ColorF color, bool interpolationLinear)
		{
			m_Graphics->SetBitmapTintEffectColor(m_ColorMatrixFx, color.r, color.g, color.b, color.a);
			m_Graphics->SetBitmapScaleEffectScale(m_ScaleFx, scale.x, scale.y);
			m_ScaleFx->SetValue(D2D1_SCALE_PROP_INTERPOLATION_MODE, interpolationLinear ? D2D1_SCALE_INTERPOLATION_MODE_LINEAR : D2D1_SCALE_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

			D2D1_RECT_F drawRec;
			drawRec.left = (frameId % m_SpritesheetInfo.m_NumXframes) * (m_SpritesheetInfo.m_FrameWidth * scale.x + m_SpritesheetInfo.m_Margin * scale.x);
			drawRec.top = floorf(frameId / (float)m_SpritesheetInfo.m_NumXframes) * (m_SpritesheetInfo.m_FrameHeight * scale.y + m_SpritesheetInfo.m_Margin * scale.y);
			drawRec.right = drawRec.left + m_SpritesheetInfo.m_FrameWidth * scale.x;
			drawRec.bottom = drawRec.top + m_SpritesheetInfo.m_FrameHeight * scale.y;

			m_Graphics->DrawEffect(m_ColorMatrixFx, dest, drawRec, interpolationLinear ? (D2D1_INTERPOLATION_MODE)D2D1_BITMAP_INTERPOLATION_MODE_LINEAR : (D2D1_INTERPOLATION_MODE)D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
		}

		void Spritesheet::DrawFrame(D2D1_POINT_2F dest, D2D1_RECT_F source, D2D1_POINT_2F scale, D2D1::ColorF color, bool interpolationLinear)
		{
			m_Graphics->SetBitmapTintEffectColor(m_ColorMatrixFx, color.r, color.g, color.b, color.a);
			m_Graphics->SetBitmapScaleEffectScale(m_ScaleFx, scale.x, scale.y);
			m_ScaleFx->SetValue(D2D1_SCALE_PROP_INTERPOLATION_MODE, interpolationLinear ? D2D1_SCALE_INTERPOLATION_MODE_LINEAR : D2D1_SCALE_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

			D2D1_RECT_F drawRec;
			drawRec.left = source.left * scale.x;
			drawRec.top = source.top * scale.y;
			drawRec.right = drawRec.left + source.right * scale.x;
			drawRec.bottom = drawRec.top + source.bottom * scale.y;

			m_Graphics->DrawEffect(m_ColorMatrixFx, dest, drawRec, interpolationLinear ? (D2D1_INTERPOLATION_MODE)D2D1_BITMAP_INTERPOLATION_MODE_LINEAR : (D2D1_INTERPOLATION_MODE)D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
		}
	}
}