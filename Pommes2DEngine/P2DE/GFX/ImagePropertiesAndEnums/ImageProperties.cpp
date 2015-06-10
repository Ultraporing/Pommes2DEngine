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
	ID_BLOCK_START = 44871;
	ID_BLOCK_END = 44872;

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
	ID_BLOCK_START = 44871;
	ID_BLOCK_END = 44872;

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

ImagePropertiesI ImagePropertiesI::ReadFromBinary(std::vector<byte>* inputData)
{
	// Read Size of SpritesheetName
	std::vector<byte>::const_iterator dataOffset = inputData->begin();
	int blockStart = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<int>(*inputData, &dataOffset);

	//std::vector<byte>::const_iterator last = inputData->begin() + sizeof(std::size_t);
	//std::vector<byte> buffer = std::vector<byte>(first, last);

	// Read spritesheet name
	std::wstring p2 = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<std::wstring>(*inputData, &dataOffset);

	// read sourceFrameIdx
	/*
	first = std::vector<byte>::const_iterator(last);
	last = std::vector<byte>::const_iterator(last + sizeof(unsigned int));
	buffer = std::vector<byte>(first, last);
	unsigned int p3 = *reinterpret_cast<unsigned int*>(&buffer[0]);*/

	unsigned int p3 = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<unsigned int>(*inputData, &dataOffset);

	// read scale X
	/*
	first = std::vector<byte>::const_iterator(last);
	last = std::vector<byte>::const_iterator(last + sizeof(float));
	buffer = std::vector<byte>(first, last);
	float p4 = *reinterpret_cast<float*>(&buffer[0]);*/

	return ImagePropertiesI();
}
	
ImagePropertiesR::ImagePropertiesR()
{
	ID_BLOCK_START = 44873;
	ID_BLOCK_END = 44874;

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
	ID_BLOCK_START = 44873;
	ID_BLOCK_END = 44874;

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

}

ImagePropertiesR ImagePropertiesR::ReadFromBinary(std::vector<byte>* inputData)
{
	//std::vector<byte> buffer = std::vector<byte>(inputData[0], inputData[sizeof(std::size_t)]);
	//std::size_t p = reinterpret_cast<std::size_t>(&buffer[0]);
	//std::size_t t = p;
	return ImagePropertiesR();
}