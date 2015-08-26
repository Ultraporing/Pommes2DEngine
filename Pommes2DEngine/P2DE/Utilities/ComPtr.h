//=================================================================================== 
// Copyright (c) Microsoft Corporation.  All rights reserved.                         
//                                                                                    
// THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY                     
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT                        
// LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND                           
// FITNESS FOR A PARTICULAR PURPOSE.                                                  
//=================================================================================== 
#ifndef COMPTR_H
	#define COMPTR_H
	#ifdef _WIN32
		#pragma once 

		// 
		// This structs acts as a smart pointer for IUnknown pointers 
		// making sure to call AddRef() and Release() as needed. 
		// 
		#include <assert.h>

		namespace P2DE
		{
			/// <summary>	Pommes2D Engine Utilities Related Namespace. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			namespace UTILITIES
			{
				template<typename T>

				/// <summary>	A com pointer. </summary>
				///
				/// <remarks>	Tobias, 22.05.2015. </remarks>
				struct ComPtr
				{
					public:

					/// <summary>	Constructor. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="lComPtr">	[in,out] (Optional) If non-null, the com pointer. </param>
					ComPtr(T* lComPtr = nullptr) : m_ComPtr(lComPtr)
					{
						static_assert(std::tr1::is_base_of<IUnknown, T>::value, "T needs to be IUnknown based");
						if (m_ComPtr)
						{
							m_ComPtr->AddRef();
						}
					}

					/// <summary>	Constructor. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="lComPtrObj">	The com pointer object. </param>
					ComPtr(const ComPtr<T>& lComPtrObj)
					{
						static_assert(std::tr1::is_base_of<IUnknown, T>::value, "T needs to be IUnknown based");
						m_ComPtr = lComPtrObj.m_ComPtr;

						if (m_ComPtr)
						{
							m_ComPtr->AddRef();
						}
					}

					/// <summary>	Constructor. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="lComPtrObj">	[in,out] The com pointer object. </param>
					ComPtr(ComPtr<T>&& lComPtrObj)
					{
						m_ComPtr = lComPtrObj.m_ComPtr;
						lComPtrObj.m_ComPtr = nullptr;
					}

					/// <summary>	Assignment operator. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="lComPtr">	[in,out] If non-null, the com pointer. </param>
					///
					/// <returns>	A shallow copy of this object. </returns>
					T* operator=(T* lComPtr)
					{
						if (m_ComPtr)
						{
							m_ComPtr->Release();
						}

						m_ComPtr = lComPtr;

						if (m_ComPtr)
						{
							m_ComPtr->AddRef();
						}

						return m_ComPtr;
					}

					/// <summary>	Assignment operator. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="lComPtrObj">	The com pointer object. </param>
					///
					/// <returns>	A shallow copy of this object. </returns>
					T* operator=(const ComPtr<T>& lComPtrObj)
					{
						if (m_ComPtr)
						{
							m_ComPtr->Release();
						}

						m_ComPtr = lComPtrObj.m_ComPtr;

						if (m_ComPtr)
						{
							m_ComPtr->AddRef();
						}

						return m_ComPtr;
					}

					/// <summary>	Destructor. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					~ComPtr()
					{
						if (m_ComPtr)
						{
							m_ComPtr->Release();
							m_ComPtr = nullptr;
						}
					}

					/// <summary>	T* casting operator. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <returns>	The result of the operation. </returns>
					operator T*() const
					{
						return m_ComPtr;
					}

					/// <summary>	Gets the interface. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <returns>	null if it fails, else the interface. </returns>
					T* GetInterface() const
					{
						return m_ComPtr;
					}

					/// <summary>	Indirection operator. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <returns>	The result of the operation. </returns>
					T& operator*() const
					{
						return *m_ComPtr;
					}

					/// <summary>	Reference operator. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <returns>	The result of the operation. </returns>
					T** operator&()
					{
						//The assert on operator& usually indicates a bug. Could be a potential memory leak. 
						// If this really what is needed, however, use GetInterface() explicitly. 
						assert(nullptr == m_ComPtr);
						return &m_ComPtr;
					}

					/// <summary>	Member dereference operator. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <returns>	The dereferenced object. </returns>
					T* operator->() const
					{
						return m_ComPtr;
					}

					/// <summary>	Logical negation operator. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <returns>	The logical inverse of this value. </returns>
					bool operator!() const
					{
						return (nullptr == m_ComPtr);
					}

					/// <summary>	Less-than comparison operator. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="lComPtr">	[in,out] If non-null, the com pointer. </param>
					///
					/// <returns>	true if the first parameter is less than the second. </returns>
					bool operator<(T* lComPtr) const
					{
						return m_ComPtr < lComPtr;
					}

					/// <summary>	Inequality operator. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="lComPtr">	[in,out] If non-null, the com pointer. </param>
					///
					/// <returns>	true if the parameters are not considered equivalent. </returns>
					bool operator!=(T* lComPtr) const
					{
						return !operator==(lComPtr);
					}

					/// <summary>	Equality operator. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="lComPtr">	[in,out] If non-null, the com pointer. </param>
					///
					/// <returns>	true if the parameters are considered equivalent. </returns>
					bool operator==(T* lComPtr) const
					{
						return m_ComPtr == lComPtr;
					}

				
					/// <summary>	Queries an interface. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="interfacePtr">	[in,out] If non-null, the interface pointer. </param>
					///
					/// <returns>	The interface. </returns>
					template <typename I>
					HRESULT QueryInterface(I **interfacePtr)
					{
						return m_ComPtr->QueryInterface(IID_PPV_ARGS(interfacePtr));
					}

					protected:
					// The internal interface pointer 
					T* m_ComPtr;
				};
			}
		}
	#endif
#endif