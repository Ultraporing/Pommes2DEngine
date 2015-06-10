#pragma once
#include <vector>

namespace P2DE
{
	namespace FILEIO
	{
		class DataTypeConverter
		{
			public:
			template<typename T>
			static std::vector<unsigned char> ConvertToByteVector(T value)
			{
				// create a buffer for convertions
				std::vector<unsigned char> byteBuffer;
		
				// Convert value
				unsigned char* p = reinterpret_cast<byte*>(&value);
				byteBuffer = std::vector<byte>(p, p + sizeof(value));

				return byteBuffer;
			};

			static std::vector<unsigned char> ConvertToByteVector(D2D1_POINT_2F point)
			{
				std::vector<unsigned char> bufferOut;
				std::vector<unsigned char> buffer;

				buffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector<float>(point.x);
				bufferOut.insert(bufferOut.end(), buffer.begin(), buffer.end());

				// convert scale Y
				buffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector<float>(point.y);
				bufferOut.insert(bufferOut.end(), buffer.begin(), buffer.end());

				return bufferOut;
			}

			static std::vector<unsigned char> ConvertToByteVector(D2D1::ColorF color)
			{
				std::vector<unsigned char> bufferOut;
				std::vector<unsigned char> buffer;

				// convert color r
				buffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector<float>(color.r);
				bufferOut.insert(bufferOut.end(), buffer.begin(), buffer.end());

				// convert color g
				buffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector<float>(color.g);
				bufferOut.insert(bufferOut.end(), buffer.begin(), buffer.end());

				// convert color b
				buffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector<float>(color.b);
				bufferOut.insert(bufferOut.end(), buffer.begin(), buffer.end());

				// convert color a
				buffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector<float>(color.a);
				bufferOut.insert(bufferOut.end(), buffer.begin(), buffer.end());

				return bufferOut;
			}

			static std::vector<unsigned char> ConvertToByteVector(std::wstring wString)
			{
				std::vector<unsigned char> bufferOut;
				std::vector<unsigned char> buffer;

				std::size_t size = wString.size() * sizeof(wString.front());
				byte const* p = reinterpret_cast<byte const*>(&wString[0]);
				buffer = P2DE::FILEIO::DataTypeConverter::ConvertToByteVector(size);
				bufferOut.insert(bufferOut.end(), buffer.begin(), buffer.end());
				buffer = std::vector<byte>(p, p + size);
				bufferOut.insert(bufferOut.end(), buffer.begin(), buffer.end());

				return bufferOut;
			}

			template<typename T>
			static T ConvertByteVectorToType(std::vector<unsigned char> data, std::vector<byte>::const_iterator* dataBegin)
			{				
				std::vector<byte>::const_iterator dataEnd = std::vector<byte>::const_iterator(*dataBegin + sizeof(T));
				std::vector<byte> buffer = std::vector<byte>(*dataBegin, dataEnd);
				*dataBegin = dataEnd;

				return *reinterpret_cast<T*>(&buffer[0]);
			}

			template<>
			static std::wstring ConvertByteVectorToType<std::wstring>(std::vector<unsigned char> data, std::vector<byte>::const_iterator* dataBegin)
			{
				std::size_t stringLength = ConvertByteVectorToType<std::size_t>(data, dataBegin);

				std::vector<byte>::const_iterator dataEnd = std::vector<byte>::const_iterator(*dataBegin + stringLength);
				std::vector<byte> buffer = std::vector<byte>(*dataBegin, dataEnd);
				*dataBegin = dataEnd;

				return std::wstring(reinterpret_cast<wchar_t*>(buffer.data()), buffer.size() / sizeof(wchar_t));
			}

		};
	}
}
