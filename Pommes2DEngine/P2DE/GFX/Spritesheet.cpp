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
			m_ScaleRotateFx = NULL;
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
					MessageBox(NULL, errorString.c_str(), L"(ReloadSpritesheetBitmap) Spritesheet Loading Error", MB_ICONERROR | MB_OK);

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
				MessageBox(NULL, errorString.c_str(), L"(LoadBitmapFromFile) Spritesheet Loading Error", MB_ICONERROR | MB_OK);
				return false;
			}

			if (!m_Graphics->CreateBitmapScaleRotateEffect(&m_ScaleRotateFx, m_SpritesheetBitmap))
			{
				MessageBox(NULL, errorString.c_str(), L"(CreateBitmapScaleEffect) Spritesheet Loading Error", MB_ICONERROR | MB_OK);
				return false;
			}

			P2DE::UTILITIES::ComPtr<ID2D1Image> tmpImg;
			m_ScaleRotateFx->GetOutput(&tmpImg);

			if (!m_Graphics->CreateBitmapTintEffect(&m_ColorMatrixFx, tmpImg, 1.0f, 1.0f, 1.0f))
			{
				MessageBox(NULL, errorString.c_str(), L"(CreateBitmapTintEffect) Spritesheet Loading Error", MB_ICONERROR | MB_OK);
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

			if (m_ScaleRotateFx)
			{
				m_ScaleRotateFx->Release();
				m_ScaleRotateFx = NULL;
			}

			return true;
		}

		bool Spritesheet::ReloadSpritesheetBitmap()
		{
			if (!m_Graphics->LoadBitmapFromFile(m_SpritesheetInfo.GetFullRelativeBitmapPath().c_str(), &m_SpritesheetBitmap))
				return false;

			if (!m_Graphics->CreateBitmapScaleRotateEffect(&m_ScaleRotateFx, m_SpritesheetBitmap))
				return false;

			P2DE::UTILITIES::ComPtr<ID2D1Image> tmpImg;
			m_ScaleRotateFx->GetOutput(&tmpImg);

			if (!m_Graphics->CreateBitmapTintEffect(&m_ColorMatrixFx, tmpImg, 1.0f, 1.0f, 1.0f))
				return false;	

			return true;
		}

		D2D1_RECT_F Spritesheet::CreateDrawRect(unsigned int frameId)
		{
			D2D1_RECT_F drawRec;
			drawRec.left = (frameId % m_SpritesheetInfo.m_NumXframes) * (m_SpritesheetInfo.m_FrameWidth + m_SpritesheetInfo.m_Margin);
			drawRec.top = floorf(frameId / (float)m_SpritesheetInfo.m_NumXframes) * (m_SpritesheetInfo.m_FrameHeight + m_SpritesheetInfo.m_Margin);
			drawRec.right = drawRec.left + m_SpritesheetInfo.m_FrameWidth;
			drawRec.bottom = drawRec.top + m_SpritesheetInfo.m_FrameHeight;

			return drawRec;
		}

		D2D1_RECT_F Spritesheet::CreateDrawRect(D2D1_RECT_F source)
		{
			D2D1_RECT_F drawRec;
			drawRec.left = source.left;
			drawRec.top = source.top;
			drawRec.right = drawRec.left + source.right;
			drawRec.bottom = drawRec.top + source.bottom;

			return drawRec;
		}

		void Spritesheet::CheckFlipMode(const D2D1_RECT_F& drawRect, const SPRITE_FLIP_MODE& flipMode, const D2D1_POINT_2F& scale, const D2D1_POINT_2F* rotationPoint, D2D1_POINT_2F* destOffset, D2D1_POINT_2F* scaleFlip, D2D1_POINT_2F* newRotationPoint)
		{
			D2D1_POINT_2F frameSize = D2D1::Point2F(drawRect.right - drawRect.left, drawRect.bottom - drawRect.top);

			if (flipMode & SPRITE_FLIP_MODE::HORIZONTAL || flipMode & SPRITE_FLIP_MODE::VERTICAL)
			{
				if (flipMode & SPRITE_FLIP_MODE::HORIZONTAL)
				{
					if (destOffset)
						(*destOffset).x = frameSize.x * scale.x;
					if (scaleFlip)
						(*scaleFlip).x = -1.0f;
					if (newRotationPoint && rotationPoint)
						(*newRotationPoint).x = (*rotationPoint).x * scale.x - (frameSize.x * scale.x);
				}

				if (flipMode & SPRITE_FLIP_MODE::VERTICAL)
				{
					if (destOffset)
						(*destOffset).y = frameSize.y * scale.y;
					if (scaleFlip)
						(*scaleFlip).y = -1.0f;
					if (newRotationPoint && rotationPoint)
						(*newRotationPoint).y = (*rotationPoint).y * scale.y - (frameSize.y * scale.y);
				}
			}
			else
			{
				if (newRotationPoint && rotationPoint)
				{
					(*newRotationPoint).x = (*rotationPoint).x * scale.x;
					(*newRotationPoint).y = (*rotationPoint).y * scale.y;
				}
			}
		}

		D2D1_POINT_2F Spritesheet::SetupDrawFrameCenterRotated(const D2D1_RECT_F& drawRect, const D2D1_POINT_2F& scale, const D2D1::ColorF& color, const float& rotateDegree, const SPRITE_FLIP_MODE& flipMode, const bool& interpolationLinear)
		{
			if (m_IntermediateOutputImage)
			{
				m_IntermediateOutputImage->Release();
				m_IntermediateOutputImage = NULL;
			}

			D2D1_POINT_2F destOffset = D2D1::Point2F();
			D2D1_POINT_2F scaleFlip = D2D1::Point2F(1.0f, 1.0f);;

			CheckFlipMode(drawRect, flipMode, scale, nullptr, &destOffset, &scaleFlip, nullptr);

			m_Graphics->CreateBitmapFromBitmapRegion(m_SpritesheetBitmap, D2D1::RectU(drawRect.left, drawRect.top, drawRect.right, drawRect.bottom), &m_IntermediateOutputImage);

			m_ScaleRotateFx->SetInput(0, m_IntermediateOutputImage);
			m_Graphics->SetBitmapScaleRotate(m_ScaleRotateFx, scale.x * scaleFlip.x, scale.y * scaleFlip.y, rotateDegree, D2D1::Point2F(scaleFlip.x* (m_SpritesheetInfo.m_FrameWidth * scale.x * 0.5f), scaleFlip.y * (m_SpritesheetInfo.m_FrameHeight * scale.y * 0.5f)));
			m_ScaleRotateFx->SetValue(D2D1_2DAFFINETRANSFORM_PROP_INTERPOLATION_MODE, interpolationLinear ? D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE_LINEAR : D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

			P2DE::UTILITIES::ComPtr<ID2D1Image> tmpImg;
			m_ScaleRotateFx->GetOutput(&tmpImg);

			m_ColorMatrixFx->SetInput(0, tmpImg);
			m_Graphics->SetBitmapTintEffectColor(m_ColorMatrixFx, color.r, color.g, color.b, color.a);

			return destOffset;
		}

		D2D1_POINT_2F Spritesheet::SetupDrawFramePointRotated(const D2D1_RECT_F& drawRect, const D2D1_POINT_2F& scale, const D2D1::ColorF& color, const float& rotateDegree, const D2D1_POINT_2F& rotatePoint, const SPRITE_FLIP_MODE& flipMode, const bool& interpolationLinear)
		{
			if (m_IntermediateOutputImage)
			{
				m_IntermediateOutputImage->Release();
				m_IntermediateOutputImage = NULL;
			}

			D2D1_POINT_2F destOffset = D2D1::Point2F();
			D2D1_POINT_2F scaleFlip = D2D1::Point2F(1.0f, 1.0f);
			D2D1_POINT_2F newRotationPoint = D2D1::Point2F();
			CheckFlipMode(drawRect, flipMode, scale, &rotatePoint, &destOffset, &scaleFlip, &newRotationPoint);

			m_Graphics->CreateBitmapFromBitmapRegion(m_SpritesheetBitmap, D2D1::RectU(drawRect.left, drawRect.top, drawRect.right, drawRect.bottom), &m_IntermediateOutputImage);

			m_ScaleRotateFx->SetInput(0, m_IntermediateOutputImage);
			m_Graphics->SetBitmapScaleRotate(m_ScaleRotateFx, scale.x * scaleFlip.x, scale.y * scaleFlip.y, rotateDegree, D2D1::Point2F(newRotationPoint.x, newRotationPoint.y));
			m_ScaleRotateFx->SetValue(D2D1_2DAFFINETRANSFORM_PROP_INTERPOLATION_MODE, interpolationLinear ? D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE_LINEAR : D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

			P2DE::UTILITIES::ComPtr<ID2D1Image> tmpImg;
			m_ScaleRotateFx->GetOutput(&tmpImg);

			m_ColorMatrixFx->SetInput(0, tmpImg);
			m_Graphics->SetBitmapTintEffectColor(m_ColorMatrixFx, color.r, color.g, color.b, color.a);

			return destOffset;
		}

		void Spritesheet::DrawFramePointRotated(D2D1_POINT_2F dest, unsigned int frameId, D2D1_POINT_2F scale, D2D1::ColorF color, float rotateDegree, D2D1_POINT_2F rotatePoint, SPRITE_FLIP_MODE flipMode, bool interpolationLinear)
		{
			D2D1_RECT_F drawRec = CreateDrawRect(frameId);
			
			D2D1_POINT_2F destOffset = SetupDrawFramePointRotated(drawRec, scale, color, rotateDegree, rotatePoint, flipMode, interpolationLinear);
			
			m_Graphics->DrawEffect(m_ColorMatrixFx, D2D1::Point2F(dest.x + destOffset.x, dest.y + destOffset.y), interpolationLinear ? (D2D1_INTERPOLATION_MODE)D2D1_BITMAP_INTERPOLATION_MODE_LINEAR : (D2D1_INTERPOLATION_MODE)D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
		}

		void Spritesheet::DrawFramePointRotated(D2D1_POINT_2F dest, D2D1_RECT_F source, D2D1_POINT_2F scale, D2D1::ColorF color, float rotateDegree, D2D1_POINT_2F rotatePoint, SPRITE_FLIP_MODE flipMode, bool interpolationLinear)
		{
			D2D1_RECT_F drawRec = CreateDrawRect(source);

			D2D1_POINT_2F destOffset = SetupDrawFramePointRotated(drawRec, scale, color, rotateDegree, rotatePoint, flipMode, interpolationLinear);

			m_Graphics->DrawEffect(m_ColorMatrixFx, D2D1::Point2F(dest.x + destOffset.x, dest.y + destOffset.y), interpolationLinear ? (D2D1_INTERPOLATION_MODE)D2D1_BITMAP_INTERPOLATION_MODE_LINEAR : (D2D1_INTERPOLATION_MODE)D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
		}

		void Spritesheet::DrawFrameCenterRotated(D2D1_POINT_2F dest, unsigned int frameId, D2D1_POINT_2F scale, D2D1::ColorF color, float rotateDegree, SPRITE_FLIP_MODE flipMode, bool interpolationLinear)
		{
			D2D1_RECT_F drawRec = CreateDrawRect(frameId);

			D2D1_POINT_2F destOffset = SetupDrawFrameCenterRotated(drawRec, scale, color, rotateDegree, flipMode, interpolationLinear);

			m_Graphics->DrawEffect(m_ColorMatrixFx, D2D1::Point2F(dest.x + destOffset.x, dest.y + destOffset.y), interpolationLinear ? (D2D1_INTERPOLATION_MODE)D2D1_BITMAP_INTERPOLATION_MODE_LINEAR : (D2D1_INTERPOLATION_MODE)D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
		}

		void Spritesheet::DrawFrameCenterRotated(D2D1_POINT_2F dest, D2D1_RECT_F source, D2D1_POINT_2F scale, D2D1::ColorF color, float rotateDegree, SPRITE_FLIP_MODE flipMode, bool interpolationLinear)
		{
			D2D1_RECT_F drawRec = CreateDrawRect(source);

			D2D1_POINT_2F destOffset = SetupDrawFrameCenterRotated(drawRec, scale, color, rotateDegree, flipMode, interpolationLinear);

			m_Graphics->DrawEffect(m_ColorMatrixFx, D2D1::Point2F(dest.x + destOffset.x, dest.y + destOffset.y), interpolationLinear ? (D2D1_INTERPOLATION_MODE)D2D1_BITMAP_INTERPOLATION_MODE_LINEAR : (D2D1_INTERPOLATION_MODE)D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
		}
	}
}