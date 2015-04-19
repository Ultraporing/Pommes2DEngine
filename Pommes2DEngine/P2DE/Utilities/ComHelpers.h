//=================================================================================== 
// Copyright (c) Microsoft Corporation.  All rights reserved.                         
//                                                                                    
// THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY                     
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT                        
// LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND                           
// FITNESS FOR A PARTICULAR PURPOSE.                                                  
//=================================================================================== 


#pragma once 
#include "ComPtr.h" 
#include <wincodec.h>

namespace P2DE
{
	namespace UTILITIES
	{
		template<class T>
		HRESULT AssignToOutputPointer(T** pp, const ComPtr<T> &p)
		{
			assert(pp);
			*pp = p;
			if (nullptr != (*pp))
			{
				(*pp)->AddRef();
			}

			return S_OK;
		}

		HRESULT GetWICFactory(IWICImagingFactory** factory)
		{
			static ComPtr<IWICImagingFactory> m_pWICFactory;
			HRESULT hr = S_OK;

			if (nullptr == m_pWICFactory)
			{
				hr = CoCreateInstance(
					CLSID_WICImagingFactory, nullptr,
					CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
			}

			if (SUCCEEDED(hr))
			{
				hr = AssignToOutputPointer(factory, m_pWICFactory);
			}

			return hr;
		}
	}
}