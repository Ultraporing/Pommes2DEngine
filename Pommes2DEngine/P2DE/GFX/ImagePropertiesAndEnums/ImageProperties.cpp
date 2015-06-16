#include "ImageProperties.h"
#include "../../FileIO/DataTypeConverter.h"

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
	InitDatastructureIDs();
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

void ImagePropertiesI::InitDatastructureIDs()
{
	ID_BLOCK_START = static_cast<DatastructureID>(DatastructureIDs::ImagePropertiesI_START);
	ID_BLOCK_END = static_cast<DatastructureID>(DatastructureIDs::ImagePropertiesI_END);
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
	InitDatastructureIDs();
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

void ImagePropertiesI::WriteToBinary(std::vector<byte>* outputData)
{
	// create a buffer for convertions
	std::vector<byte> byteBuffer;

	// convert ID_BLOCK_START
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(ID_BLOCK_START);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// Convert spritesheetName to bytes and append it to output data
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_SpritesheetName);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert sourceFrameIdx
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_SourceFrameIdx);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert scale
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_Scale);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert color
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_Color);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert rotDegree
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_RotateDegree);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert rotFromCenter
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_RotateFromCenter);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert rotationPoint
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_RotatePoint);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert FlipMode
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_FlipMode);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert interpolation mode
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_InterpolationMode);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert ID_BLOCK_END
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(ID_BLOCK_END);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
}

bool ImagePropertiesI::ReadFromBinary(std::vector<byte>* inputData, ImagePropertiesI& readImageProperties)
{
	// Create Data Offset
	std::vector<byte>::const_iterator dataOffset = inputData->begin();

	// Read Block Start ID
	if (P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<DatastructureID>(*inputData, &dataOffset) != (DatastructureID)DatastructureIDs::ImagePropertiesI_START)
	{
		MessageBox(NULL, L"ID_BLOCK_START is invalid or missing", L"ReadFromBinary ImagePropertiesI", MB_OK);
		return false;
	}

	// Read spritesheet name
	readImageProperties.m_SpritesheetName = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<std::wstring>(*inputData, &dataOffset);

	// Read sourceFrameIdx
	readImageProperties.m_SourceFrameIdx = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<unsigned int>(*inputData, &dataOffset);

	// Read scale
	readImageProperties.m_Scale = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<D2D1_POINT_2F>(*inputData, &dataOffset);

	// Read color
	readImageProperties.m_Color = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<D2D1_COLOR_F>(*inputData, &dataOffset);

	// Read rotDegree
	readImageProperties.m_RotateDegree = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<float>(*inputData, &dataOffset);

	// Read rotFromCenter
	readImageProperties.m_RotateFromCenter = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<bool>(*inputData, &dataOffset);

	// Read rotationPoint
	readImageProperties.m_RotatePoint = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<D2D1_POINT_2F>(*inputData, &dataOffset);

	// Read FlipMode
	readImageProperties.m_FlipMode = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<P2DE::GFX::SPRITE_FLIP_MODE>(*inputData, &dataOffset);

	// Read interpolation mode
	readImageProperties.m_InterpolationMode = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<P2DE::GFX::SPRITE_INTERPOLATION_MODE>(*inputData, &dataOffset);

	// Read Block End ID
	if (P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<DatastructureID>(*inputData, &dataOffset) != (DatastructureID)DatastructureIDs::ImagePropertiesI_END)
	{
		MessageBox(NULL, L"ID_BLOCK_END is invalid or missing", L"ReadFromBinary ImagePropertiesI", MB_OK);
		return false;
	}

	return true;
}
	
ImagePropertiesR::ImagePropertiesR()
{
	InitDatastructureIDs();
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

void ImagePropertiesR::InitDatastructureIDs()
{
	ID_BLOCK_START = static_cast<DatastructureID>(DatastructureIDs::ImagePropertiesR_START);
	ID_BLOCK_END = static_cast<DatastructureID>(DatastructureIDs::ImagePropertiesR_END);
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
	InitDatastructureIDs();
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

void ImagePropertiesR::WriteToBinary(std::vector<byte>* outputData)
{
	// create a buffer for convertions
	std::vector<byte> byteBuffer;

	// convert ID_BLOCK_START
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(ID_BLOCK_START);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// Convert spritesheetName to bytes and append it to output data
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_SpritesheetName);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert SourceImageRect
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_SourceImageRect);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert scale
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_Scale);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert color
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_Color);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert rotDegree
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_RotateDegree);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert rotFromCenter
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_RotateFromCenter);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert rotationPoint
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_RotatePoint);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert FlipMode
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_FlipMode);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert interpolation mode
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_InterpolationMode);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// convert ID_BLOCK_END
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(ID_BLOCK_END);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
}

bool ImagePropertiesR::ReadFromBinary(std::vector<byte>* inputData, ImagePropertiesR& readImageProperties)
{
	// Create Data Offset
	std::vector<byte>::const_iterator dataOffset = inputData->begin();

	// Read Block Start ID
	if (P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<DatastructureID>(*inputData, &dataOffset) != (DatastructureID)DatastructureIDs::ImagePropertiesR_START)
	{
		MessageBox(NULL, L"ID_BLOCK_START is invalid or missing", L"ReadFromBinary ImagePropertiesR", MB_OK);
		return false;
	}

	// Read spritesheet name
	readImageProperties.m_SpritesheetName = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<std::wstring>(*inputData, &dataOffset);

	// Read sourceRect
	readImageProperties.m_SourceImageRect = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<D2D1_RECT_F>(*inputData, &dataOffset);

	// Read scale
	readImageProperties.m_Scale = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<D2D1_POINT_2F>(*inputData, &dataOffset);

	// Read color
	readImageProperties.m_Color = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<D2D1_COLOR_F>(*inputData, &dataOffset);

	// Read rotDegree
	readImageProperties.m_RotateDegree = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<float>(*inputData, &dataOffset);

	// Read rotFromCenter
	readImageProperties.m_RotateFromCenter = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<bool>(*inputData, &dataOffset);

	// Read rotationPoint
	readImageProperties.m_RotatePoint = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<D2D1_POINT_2F>(*inputData, &dataOffset);

	// Read FlipMode
	readImageProperties.m_FlipMode = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<P2DE::GFX::SPRITE_FLIP_MODE>(*inputData, &dataOffset);

	// Read interpolation mode
	readImageProperties.m_InterpolationMode = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<P2DE::GFX::SPRITE_INTERPOLATION_MODE>(*inputData, &dataOffset);

	// Read Block End ID
	if (P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<DatastructureID>(*inputData, &dataOffset) != (DatastructureID)DatastructureIDs::ImagePropertiesR_END)
	{
		MessageBox(NULL, L"ID_BLOCK_END is invalid or missing", L"ReadFromBinary ImagePropertiesR", MB_OK);
		return false;
	}

	return true;
}