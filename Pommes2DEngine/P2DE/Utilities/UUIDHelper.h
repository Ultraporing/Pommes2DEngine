#pragma once
#include <wrl\client.h>
#include <string>
#include <sstream>
#include "../Common.h"
using namespace Microsoft::WRL;

namespace P2DE
{
	namespace UTILITIES
	{
		P2DE_DECLSPEC UUID CreateUUID()
		{
			UUID uuid = { 0 };
			if (UuidCreate(&uuid) != RPC_S_OK)
			{
				std::wstringstream wss;
				wss << L"Error: Failed to create UUID!";
				MessageBox(NULL, wss.str().c_str(), L"Error", MB_ICONERROR);

				return;
			}

			return uuid;
		}
		
		P2DE_DECLSPEC std::wstring UUIDtoWstring(const UUID* uuid)
		{
			std::wstring outStr = L"";
			RPC_WSTR szUuid = NULL;
			if (UuidToString(uuid, &szUuid) != RPC_S_OK)
			{
				std::wstringstream wss;
				wss << L"Error: Failed to convert UUID to string!";
				MessageBox(NULL, wss.str().c_str(), L"Error", MB_ICONERROR);

				return;
			}

			outStr = (wchar_t*)szUuid;
			RpcStringFree(&szUuid);

			return outStr;
		}
	}
}