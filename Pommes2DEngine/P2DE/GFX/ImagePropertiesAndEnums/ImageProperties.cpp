#include "ImageProperties.h"
#include "../../FileIO/DataTypeConverter.h"

using namespace P2DE::GFX;
	
ImageProperties::ImageProperties()
{
	InitDatastructureIDs();
	m_diffrentToLastFlags = 0;
	m_SpritesheetName = L"";
	m_SourceFrameIdx = 0;
	m_SourceImageRect = D2D1::RectF();
	m_Scale = D2D1::Point2F();
	m_Color = D2D1::ColorF(D2D1::ColorF::White);
	m_RotateDegree = 0;
	m_RotateFromCenter = false;
	m_RotatePoint = D2D1::Point2F();
	m_FlipMode = SPRITE_FLIP_MODE::NONE;
	m_InterpolationMode = SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR;
}

void ImageProperties::InitDatastructureIDs()
{
	ID_BLOCK_START = static_cast<DatastructureID>(DatastructureIDs::ImageProperties_START);
	ID_BLOCK_END = static_cast<DatastructureID>(DatastructureIDs::ImageProperties_END);
}

ImageProperties::ImageProperties(
	std::wstring spritesheetName,
	unsigned int sourceFrameIdx,
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
	m_diffrentToLastFlags = 0;
	m_SpritesheetName = spritesheetName;
	m_SourceFrameIdx = sourceFrameIdx;
	m_SourceImageRect = sourceImageRect;
	m_Scale = scale;
	m_Color = color;
	m_RotateDegree = rotateDegree;
	m_RotateFromCenter = rotateFromCenter;
	m_RotatePoint = rotatePoint;
	m_FlipMode = flipMode;
	m_InterpolationMode = interpolationMode;
}

bool ImageProperties::UsesSourceImageRect() const
{
	if (m_SourceImageRect.bottom == 0 && m_SourceImageRect.top == 0 && m_SourceImageRect.right == 0 && m_SourceImageRect.left == 0)
		return false;

	return true;
}

void ImageProperties::SetDiffFlags(ImageProperties* previousImageProperty)
{
	if (!previousImageProperty)
	{
		m_diffrentToLastFlags = ~0;
	}
	else
	{
		if (m_SpritesheetName.compare(previousImageProperty->m_SpritesheetName) != 0)
		{
			m_diffrentToLastFlags |= ImageProperties::ImagePropertiesDiffFlags::IPDF_SPRITESHEET_NAME;
		}

		if (m_SourceFrameIdx != previousImageProperty->m_SourceFrameIdx)
		{
			m_diffrentToLastFlags |= ImageProperties::ImagePropertiesDiffFlags::IPDF_SOURCE_FRAME_IDX;
		}

		if (m_SourceImageRect.bottom != previousImageProperty->m_SourceImageRect.bottom ||
			m_SourceImageRect.top != previousImageProperty->m_SourceImageRect.top ||
			m_SourceImageRect.right != previousImageProperty->m_SourceImageRect.right ||
			m_SourceImageRect.left != previousImageProperty->m_SourceImageRect.left)
		{
			m_diffrentToLastFlags |= ImageProperties::ImagePropertiesDiffFlags::IPDF_SOURCE_IMAGE_RECT;
		}

		if (m_Scale.x != previousImageProperty->m_Scale.x ||
			m_Scale.y != previousImageProperty->m_Scale.y)
		{
			m_diffrentToLastFlags |= ImageProperties::ImagePropertiesDiffFlags::IPDF_SCALE;
		}

		if (m_Color.r != previousImageProperty->m_Color.r ||
			m_Color.g != previousImageProperty->m_Color.g ||
			m_Color.b != previousImageProperty->m_Color.b ||
			m_Color.a != previousImageProperty->m_Color.a)
		{
			m_diffrentToLastFlags |= ImageProperties::ImagePropertiesDiffFlags::IPDF_COLOR;
		}

		if (m_RotateDegree != previousImageProperty->m_RotateDegree)
		{
			m_diffrentToLastFlags |= ImageProperties::ImagePropertiesDiffFlags::IPDF_ROTATE_DEGREE;
		}

		if (m_RotateFromCenter != previousImageProperty->m_RotateFromCenter)
		{
			m_diffrentToLastFlags |= ImageProperties::ImagePropertiesDiffFlags::IPDF_ROTATE_FROM_CENTER;
		}

		if (m_RotatePoint.x != previousImageProperty->m_RotatePoint.x ||
			m_RotatePoint.y != previousImageProperty->m_RotatePoint.y)
		{
			m_diffrentToLastFlags |= ImageProperties::ImagePropertiesDiffFlags::IPDF_ROTATE_POINT;
		}

		if (m_FlipMode != previousImageProperty->m_FlipMode)
		{
			m_diffrentToLastFlags |= ImageProperties::ImagePropertiesDiffFlags::IPDF_FLIP_MODE;
		}

		if (m_InterpolationMode != previousImageProperty->m_InterpolationMode)
		{
			m_diffrentToLastFlags |= ImageProperties::ImagePropertiesDiffFlags::IPDF_INTERPOLATION_MODE;
		}
	}
}

void ImageProperties::WriteToBinary(std::vector<byte>* outputData)
{
	WriteToBinary(outputData, NULL);
}

void ImageProperties::WriteToBinary(std::vector<byte>* outputData, ImageProperties* previousImageProperty)
{
	// create a buffer for Writing
	std::vector<byte> byteBuffer;

	// Write ID_BLOCK_START
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(ID_BLOCK_START);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// sets all bitflags for changed variables
	SetDiffFlags(previousImageProperty);

	// Write the Diff Bitflags
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_diffrentToLastFlags);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// write only delta if we got a previous image property. Else write all

	if (m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_SPRITESHEET_NAME)
	{
		// Write spritesheetName to bytes and append it to output data
		byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_SpritesheetName);
		outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
	}
		
	if (m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_SOURCE_FRAME_IDX)
	{
		// Write sourceFrameIdx
		byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_SourceFrameIdx);
		outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
	}
		
	if (m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_SOURCE_IMAGE_RECT)
	{
		// Write SourceImageRect
		byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_SourceImageRect);
		outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
	}
		
	if (m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_SCALE)
	{
		// Write scale
		byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_Scale);
		outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
	}
		
	if (m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_COLOR)
	{
		// Write color
		byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_Color);
		outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
	}

	if (m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_ROTATE_DEGREE)
	{
		// Write rotDegree
		byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_RotateDegree);
		outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
	}

	if (m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_ROTATE_FROM_CENTER)
	{
		// Write rotFromCenter
		byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_RotateFromCenter);
		outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
	}

	if (m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_ROTATE_POINT)
	{
		// Write rotationPoint
		byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_RotatePoint);
		outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
	}
		
	if (m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_FLIP_MODE)
	{
		// Write FlipMode
		byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_FlipMode);
		outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
	}

	if (m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_INTERPOLATION_MODE)
	{
		// Write interpolation mode
		byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(m_InterpolationMode);
		outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
	}	
	
	// Write ID_BLOCK_END
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(ID_BLOCK_END);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
}

void ImageProperties::WriteMultipleToBinary(std::vector<byte>* outputData, std::vector<ImageProperties>* imagePropertiesVector)
{
	if (!imagePropertiesVector || imagePropertiesVector->size() == 0)
		return;

	// create a buffer for convertions
	std::vector<byte> byteBuffer;

	// convert ImagePropertiesVector_START
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(DatastructureIDs::ImagePropertiesVector_START);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// write amount of properties
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector((int)imagePropertiesVector->size());
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());

	// write fist property
	imagePropertiesVector->at(0).WriteToBinary(outputData);

	// write rest of the image properties if vector got more than 1
	if (imagePropertiesVector->size() > 1)
	{
		for (unsigned int i = 1; i < imagePropertiesVector->size(); i++)
		{
			imagePropertiesVector->at(i).WriteToBinary(outputData, &imagePropertiesVector->at(i - 1));
		}
	}

	// write ImagePropertiesVector_END
	byteBuffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(DatastructureIDs::ImagePropertiesVector_END);
	outputData->insert(outputData->end(), byteBuffer.begin(), byteBuffer.end());
}

bool ImageProperties::ReadFromBinary(std::vector<byte>* inputData, std::vector<byte>::const_iterator* offset, ImageProperties* previousImageProperty, ImageProperties& readImageProperties)
{
	// Create Data Offset
	std::vector<byte>::const_iterator dataOffset = std::vector<byte>::const_iterator(inputData->begin() + std::distance<std::vector<byte>::const_iterator>(inputData->begin(), *offset));

	// Read Block Start ID
	if (P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<DatastructureID>(*inputData, &dataOffset) != (DatastructureID)DatastructureIDs::ImageProperties_START)
	{
		MessageBox(NULL, L"ID_BLOCK_START is invalid or missing", L"ReadFromBinary ImageProperties", MB_OK);
		return false;
	}

	// Read the Diff Bitflags
	readImageProperties.m_diffrentToLastFlags = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<int>(*inputData, &dataOffset);

	// Read only Diffs, else set variables to previous image property

	if (readImageProperties.m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_SPRITESHEET_NAME)
	{
		// Read spritesheet name
		readImageProperties.m_SpritesheetName = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<std::wstring>(*inputData, &dataOffset);
	}
	else
	{
		readImageProperties.m_SpritesheetName = previousImageProperty->m_SpritesheetName;
	}

	if (readImageProperties.m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_SOURCE_FRAME_IDX)
	{
		// Read sourceFrameIdx
		readImageProperties.m_SourceFrameIdx = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<unsigned int>(*inputData, &dataOffset);
	}
	else
	{
		readImageProperties.m_SourceFrameIdx = previousImageProperty->m_SourceFrameIdx;
	}

	if (readImageProperties.m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_SOURCE_IMAGE_RECT)
	{
		// Read sourceRect
		readImageProperties.m_SourceImageRect = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<D2D1_RECT_F>(*inputData, &dataOffset);
	}
	else
	{
		readImageProperties.m_SourceImageRect = previousImageProperty->m_SourceImageRect;
	}

	if (readImageProperties.m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_SCALE)
	{
		// Read scale
		readImageProperties.m_Scale = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<D2D1_POINT_2F>(*inputData, &dataOffset);
	}
	else
	{
		readImageProperties.m_Scale = previousImageProperty->m_Scale;
	}

	if (readImageProperties.m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_COLOR)
	{
		// Read color
		readImageProperties.m_Color = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<D2D1_COLOR_F>(*inputData, &dataOffset);
	}
	else
	{
		readImageProperties.m_Color = previousImageProperty->m_Color;
	}

	if (readImageProperties.m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_ROTATE_DEGREE)
	{
		// Read rotDegree
		readImageProperties.m_RotateDegree = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<float>(*inputData, &dataOffset);
	}
	else
	{
		readImageProperties.m_RotateDegree = previousImageProperty->m_RotateDegree;
	}

	if (readImageProperties.m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_ROTATE_FROM_CENTER)
	{
		// Read rotFromCenter
		readImageProperties.m_RotateFromCenter = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<bool>(*inputData, &dataOffset);
	}
	else
	{
		readImageProperties.m_RotateFromCenter = previousImageProperty->m_RotateFromCenter;
	}

	if (readImageProperties.m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_ROTATE_POINT)
	{
		// Read rotationPoint
		readImageProperties.m_RotatePoint = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<D2D1_POINT_2F>(*inputData, &dataOffset);
	}
	else
	{
		readImageProperties.m_RotatePoint = previousImageProperty->m_RotatePoint;
	}

	if (readImageProperties.m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_FLIP_MODE)
	{
		// Read FlipMode
		readImageProperties.m_FlipMode = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<P2DE::GFX::SPRITE_FLIP_MODE>(*inputData, &dataOffset);
	}
	else
	{
		readImageProperties.m_FlipMode = previousImageProperty->m_FlipMode;
	}

	if (readImageProperties.m_diffrentToLastFlags & ImageProperties::ImagePropertiesDiffFlags::IPDF_INTERPOLATION_MODE)
	{
		// Read interpolation mode
		readImageProperties.m_InterpolationMode = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<P2DE::GFX::SPRITE_INTERPOLATION_MODE>(*inputData, &dataOffset);
	}
	else
	{
		readImageProperties.m_InterpolationMode = previousImageProperty->m_InterpolationMode;
	}

	// Read Block End ID
	if (P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<DatastructureID>(*inputData, &dataOffset) != (DatastructureID)DatastructureIDs::ImageProperties_END)
	{
		MessageBox(NULL, L"ID_BLOCK_END is invalid or missing", L"ReadFromBinary ImageProperties", MB_OK);
		return false;
	}

	*offset = dataOffset;

	return true;
}

bool ImageProperties::ReadMultipleFromBinary(std::vector<byte>* inputData, std::vector<ImageProperties>& readImagePropertiesVector)
{
	// Create Data Offset
	std::vector<byte>::const_iterator dataOffset = inputData->begin();
	ImageProperties buffer;

	// Read Block Start ID
	if (P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<DatastructureID>(*inputData, &dataOffset) != (DatastructureID)DatastructureIDs::ImagePropertiesVector_START)
	{
		MessageBox(NULL, L"ID_BLOCK_START is invalid or missing", L"ReadMultipleFromBinary ImageProperties", MB_OK);
		return false;
	}

	// amount of ImageProperty data structures to read
	int amount = P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<int>(*inputData, &dataOffset);

	readImagePropertiesVector = std::vector<ImageProperties>();

	ImageProperties::ReadFromBinary(inputData, &dataOffset, NULL, buffer);
	
	auto it = readImagePropertiesVector.begin();
	readImagePropertiesVector.insert(it, buffer);

	for (int i = 1; i < amount; i++)
	{
		ImageProperties::ReadFromBinary(inputData, &dataOffset, &readImagePropertiesVector.at(i - 1), buffer);
		readImagePropertiesVector.push_back(buffer);
	}

	// Read Block End ID
	if (P2DE::FILEIO::DataTypeConverter::ConvertByteVectorToType<DatastructureID>(*inputData, &dataOffset) != (DatastructureID)DatastructureIDs::ImagePropertiesVector_END)
	{
		MessageBox(NULL, L"ID_BLOCK_END is invalid or missing", L"ReadMultipleFromBinary ImageProperties", MB_OK);
		return false;
	}

	return true;
}