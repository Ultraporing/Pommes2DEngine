#include "ImageProperties.h"

using namespace P2DE::GFX;

BaseImageProperties::BaseImageProperties()
{
	m_SpritesheetName = L"";
	m_Scale = D2D1::Point2F();
	m_Color = D2D1::ColorF(D2D1::ColorF::White);
	m_RotateDegree = 0;
	m_RotateFromCenter = false;
	m_RotatePoint = D2D1::Point2F();
	m_FlipMode = SPRITE_FLIP_MODE::NONE;
	m_InterpolationMode = SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR;
}

ImagePropertiesI::ImagePropertiesI()
{
	m_SpritesheetName = L"";
	m_SourceFrameIdx = 0;
	m_Scale = D2D1::Point2F();
	m_Color = D2D1::ColorF(D2D1::ColorF::White);
	m_RotateDegree = 0;
	m_RotateFromCenter = false;
	m_RotatePoint = D2D1::Point2F();
	m_FlipMode = SPRITE_FLIP_MODE::NONE;
	m_InterpolationMode = SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR;
}

ImagePropertiesI::ImagePropertiesI(
	std::wstring spritesheetName,
	unsigned int sourceFrameIdx,
	D2D1_POINT_2F scale,
	D2D1::ColorF color,
	float rotateDegree,
	bool rotateFromCenter,
	D2D1_POINT_2F rotatePoint,
	SPRITE_FLIP_MODE flipMode,
	SPRITE_INTERPOLATION_MODE interpolationMode)
{
	m_SpritesheetName = spritesheetName;
	m_SourceFrameIdx = sourceFrameIdx;
	m_Scale = scale;
	m_Color = color;
	m_RotateDegree = rotateDegree;
	m_RotateFromCenter = rotateFromCenter;
	m_RotatePoint = rotatePoint;
	m_FlipMode = flipMode;
	m_InterpolationMode = interpolationMode;
}
	
ImagePropertiesR::ImagePropertiesR()
{
	m_SpritesheetName = L"";
	m_SourceImageRect = D2D1::RectF();
	m_Scale = D2D1::Point2F();
	m_Color = D2D1::ColorF(D2D1::ColorF::White);
	m_RotateDegree = 0;
	m_RotateFromCenter = false;
	m_RotatePoint = D2D1::Point2F();
	m_FlipMode = SPRITE_FLIP_MODE::NONE;
	m_InterpolationMode = SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR;
}

ImagePropertiesR::ImagePropertiesR(
	std::wstring spritesheetName,
	D2D1_RECT_F sourceImageRect,
	D2D1_POINT_2F scale,
	D2D1::ColorF color,
	float rotateDegree,
	bool rotateFromCenter,
	D2D1_POINT_2F rotatePoint,
	SPRITE_FLIP_MODE flipMode,
	SPRITE_INTERPOLATION_MODE interpolationMode)
{
	m_SpritesheetName = spritesheetName;
	m_SourceImageRect = sourceImageRect;
	m_Scale = scale;
	m_Color = color;
	m_RotateDegree = rotateDegree;
	m_RotateFromCenter = rotateFromCenter;
	m_RotatePoint = rotatePoint;
	m_FlipMode = flipMode;
	m_InterpolationMode = interpolationMode;
}