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
		/// <summary>	Assign to output pointer. </summary>
		///
		/// <remarks>	Tobias, 22.05.2015. </remarks>
		///
		/// <param name="pp">	[in,out] If non-null, the pp. </param>
		/// <param name="p"> 	The const ComPtr&lt;T&gt; &amp; to process. </param>
		///
		/// <returns>	A hResult. </returns>
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

		/// <summary>	Gets wic factory. </summary>
		///
		/// <remarks>	Tobias, 22.05.2015. </remarks>
		///
		/// <param name="factory">	[in,out] If non-null, the factory. </param>
		///
		/// <returns>	The wic factory. </returns>
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