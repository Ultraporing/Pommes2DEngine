//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 
////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	P2DE\GFX\Spritesheet.h
//
// summary:	Declares the spritesheet class
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
//#include "Graphics.h"
#include <d2d1_1.h>
#include <string>
#include <map>
#include "..\Utilities\ComPtr.h"

struct ID2D1Bitmap;
struct ID2D1Image;
struct ID2D1Effect;

namespace P2DE
{
	namespace GFX
	{
		class Graphics;

		enum SPRITE_INTERPOLATION_MODE
		{
			NEAREST_NEIGHBOR = D2D1_INTERPOLATION_MODE_DEFINITION_NEAREST_NEIGHBOR,
			LINEAR = D2D1_INTERPOLATION_MODE_DEFINITION_LINEAR,
			CUBIC = D2D1_INTERPOLATION_MODE_DEFINITION_CUBIC,
			MULTI_SAMPLE_LINEAR = D2D1_INTERPOLATION_MODE_DEFINITION_MULTI_SAMPLE_LINEAR,
			ANISOTROPIC = D2D1_INTERPOLATION_MODE_DEFINITION_ANISOTROPIC,
			HIGH_QUALITY_CUBIC = D2D1_INTERPOLATION_MODE_DEFINITION_HIGH_QUALITY_CUBIC,
			FORCE_DWORD = 0xffffffff
		};

		/// <summary>	Values that represent sprite flip modes. </summary>
		///
		/// <remarks>	Tobias, 26.05.2015. </remarks>
		enum SPRITE_FLIP_MODE
		{
			NONE = 0,
			HORIZONTAL = 1 << 0,
			VERTICAL = 1 << 1
		};

		/// <summary>	Information about the spritesheet. </summary>
		///
		/// <remarks>	Tobias, 18.05.2015. </remarks>
		struct SpritesheetInfo
		{
			/// <summary>	The File name. </summary>
			std::wstring m_FileName;
			/// <summary>	Relative Path of the directory. </summary>
			std::wstring m_DirPath;

			/// <summary>	Gets full relative bitmap path. </summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <returns>	The full relative bitmap path. </returns>
			std::wstring GetFullRelativeBitmapPath()
			{
				std::wstring str(m_DirPath);
				str.append(L"\\");
				str.append(m_FileName);

				return str;
			}

			/// <summary>	Number of frames in the X-Direction. </summary>
			int m_NumXframes;
			/// <summary>	Number of frames in the Y-Direction. </summary>
			int m_NumYframes;
			/// <summary>	Width of the frame. </summary>
			int m_FrameWidth;
			/// <summary>	Height of the frame. </summary>
			int m_FrameHeight;
			/// <summary>	The margin between frames. </summary>
			int m_Margin;
		};

		/// <summary>	A spritesheet. </summary>
		///
		/// <remarks>	Tobias, 18.05.2015. </remarks>
		class Spritesheet
		{
			private:
			/// <summary>	The graphics class used. </summary>
			P2DE::GFX::Graphics* m_Graphics;
			/// <summary>	The color matrix effect used for drawing the frames.</summary>
			ID2D1Effect* m_ColorMatrixFx;
			/// <summary>	The scale and Rotate effect used for drawing the frames. </summary>
			ID2D1Effect* m_ScaleRotateFx;
			/// <summary>	Information describing the spritesheet. </summary>
			SpritesheetInfo m_SpritesheetInfo;
			/// <summary>	The spritesheet bitmap. </summary>
			ID2D1Bitmap* m_SpritesheetBitmap;
			/// <summary>	The shared intermediate image cache. </summary>
			static std::map<std::pair<UINT32, UINT32>, P2DE::UTILITIES::ComPtr<ID2D1Bitmap>> m_SharedIntermediateImageCache;

			public:
			/// <summary>	Default constructor. </summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			Spritesheet();
			/// <summary>	Destructor. </summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			~Spritesheet();

			/// <summary>	Gets spritesheet information. </summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <returns>	The spritesheet information. </returns>
			SpritesheetInfo GetSpritesheetInfo() { return m_SpritesheetInfo; };		
			/// <summary>	Gets spritesheet bitmap. </summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <returns>	null if it fails, else the spritesheet bitmap. </returns>
			ID2D1Bitmap* GetSpritesheetBitmap() { return m_SpritesheetBitmap; };

			/// <summary>	Loads a spritesheet. </summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <param name="pathToSpritesheetInfoTXT">	[in] The path to spritesheet information text. </param>
			/// <param name="graphics">				   	[in] If non-null, the graphics class to be used. Sets m_Graphics to this parameter. </param>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool LoadSpritesheet(const std::wstring& pathToSpritesheetInfoTXT, P2DE::GFX::Graphics* graphics);
			/// <summary>	Unloads the spritesheet bitmap. Mostly used if we have to resize the Swapchain. </summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool UnloadSpritesheetBitmap();

			/// <summary>	Draws a frame of the spritesheet by use of the frameId. Rotates around a certain Point.</summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <param name="dest">   	[in] Destination for the frame. </param>
			/// <param name="frameId">	[in] Identifier for the frame. </param>
			/// <param name="scale">	[in] Scale for the frame. </param>
			/// <param name="color">	[in] Color tint for the frame. </param>
			/// <param name="rotateDegree">	[in] Frame rotation in Degree. </param>
			/// <param name="rotatePoint">	[in] Point to rotate frame around. </param>
			/// <param name="interpolationLinear">	[in] If TRUE Linear Interpolation is used, otherwise Nearest Neighbor. </param>
			void DrawFramePointRotated(D2D1_POINT_2F dest, unsigned int frameId, D2D1_POINT_2F scale = { 1, 1 }, D2D1::ColorF color = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), float rotateDegree = 0.0f, D2D1_POINT_2F rotatePoint = { 0, 0 }, SPRITE_FLIP_MODE flipMode = SPRITE_FLIP_MODE::NONE, const SPRITE_INTERPOLATION_MODE& interpolationMode = SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);
			/// <summary>	Draws a frame of the spritesheet by use of an source Rectangle. Rotates around a certain Point.</summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <param name="dest">   	[in] Destination for the frame. </param>
			/// <param name="source">	[in] Source rectangle of the frame. Rect: left = x, top = y, right = width, bottom = height </param>
			/// <param name="scale">	[in] Scale for the frame. </param>
			/// <param name="color">	[in] Color tint for the frame. </param>
			/// <param name="rotateDegree">	[in] Frame rotation in Degree. </param>
			/// <param name="rotatePoint">	[in] Point to rotate frame around. </param>
			/// <param name="interpolationLinear">	[in] If TRUE Linear Interpolation is used, otherwise Nearest Neighbor. </param>
			void DrawFramePointRotated(D2D1_POINT_2F dest, D2D1_RECT_F source, D2D1_POINT_2F scale = { 1, 1 }, D2D1::ColorF color = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), float rotateDegree = 0.0f, D2D1_POINT_2F rotatePoint = { 0, 0 }, SPRITE_FLIP_MODE flipMode = SPRITE_FLIP_MODE::NONE, const SPRITE_INTERPOLATION_MODE& interpolationMode = SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);
			/// <summary>	Draws a frame of the spritesheet by use of the frameId. Rotates around the center.</summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <param name="dest">   	[in] Destination for the frame. </param>
			/// <param name="frameId">	[in] Identifier for the frame. </param>
			/// <param name="scale">	[in] Scale for the frame. </param>
			/// <param name="color">	[in] Color tint for the frame. </param>
			/// <param name="rotateDegree">	[in] Frame rotation in Degree. </param>
			/// <param name="interpolationLinear">	[in] If TRUE Linear Interpolation is used, otherwise Nearest Neighbor. </param>
			void DrawFrameCenterRotated(D2D1_POINT_2F dest, unsigned int frameId, D2D1_POINT_2F scale = { 1, 1 }, D2D1::ColorF color = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), float rotateDegree = 0.0f, SPRITE_FLIP_MODE flipMode = SPRITE_FLIP_MODE::NONE, const SPRITE_INTERPOLATION_MODE& interpolationMode = SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);
			/// <summary>	Draws a frame of the spritesheet by use of an source Rectangle. Rotates around the center.</summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <param name="dest">   	[in] Destination for the frame. </param>
			/// <param name="source">	[in] Source rectangle of the frame. Rect: left = x, top = y, right = width, bottom = height </param>
			/// <param name="scale">	[in] Scale for the frame. </param>
			/// <param name="color">	[in] Color tint for the frame. </param>
			/// <param name="rotateDegree">	[in] Frame rotation in Degree. </param>
			/// <param name="interpolationLinear">	[in] If TRUE Linear Interpolation is used, otherwise Nearest Neighbor. </param>
			void DrawFrameCenterRotated(D2D1_POINT_2F dest, D2D1_RECT_F source, D2D1_POINT_2F scale = { 1, 1 }, D2D1::ColorF color = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), float rotateDegree = 0.0f, SPRITE_FLIP_MODE flipMode = SPRITE_FLIP_MODE::NONE, const SPRITE_INTERPOLATION_MODE& interpolationMode = SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);

			private:
			/// <summary>	Reload the spritesheet bitmap. Mostly used after unloading the spritesheet bitmap. </summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool ReloadSpritesheetBitmap();

			/// <summary>	Gets cached intermediate image with dimensions of the region. And copys pixels into the cached image if it exists or creates a new image and copys the pixels. </summary>
			///
			/// <remarks>	Tobias, 28.05.2015. </remarks>
			///
			/// <param name="size">	The size. </param>
			///
			/// <returns>	null if it fails, else the cached intermediate image. </returns>
			ID2D1Bitmap* GetCachedIntermediateImage(const D2D1_RECT_U& region);

			/// <summary>	Creates draw rectangle. </summary>
			///
			/// <remarks>	Tobias, 26.05.2015. </remarks>
			///
			/// <param name="frameId">	[in] Identifier for the frame. </param>
			///
			/// <returns>	The new draw rectangle. </returns>
			D2D1_RECT_F CreateDrawRect(unsigned int frameId);
			/// <summary>	Creates draw rectangle. </summary>
			///
			/// <remarks>	Tobias, 26.05.2015. </remarks>
			///
			/// <param name="source">	[in] Source rectangle of the frame. Rect: left = x, top = y, right = width, bottom = height. </param>
			///
			/// <returns>	The new draw rectangle. </returns>
			D2D1_RECT_F CreateDrawRect(D2D1_RECT_F source);

			/// <summary>	Check flip mode. </summary>
			///
			/// <remarks>	Tobias, 26.05.2015. </remarks>
			///
			/// <param name="drawRect">		   	[in] The draw rectangle. </param>
			/// <param name="flipMode">		   	[in] The flip mode. </param>
			/// <param name="scale">		   	[in] The scale. </param>
			/// <param name="rotationPoint">   	[in] If non-null and newRotationPoint non-null, The rotation point. </param>
			/// <param name="destOffset">	   	[out] If non-null, destination offset. </param>
			/// <param name="scaleFlip">	   	[out] If non-null, the scale flip. </param>
			/// <param name="newRotationPoint">	[out] If non-null and rotationPoint non-null, the new rotation point. </param>
			void CheckFlipMode(const D2D1_RECT_F& drawRect, const SPRITE_FLIP_MODE& flipMode, const D2D1_POINT_2F& scale, const D2D1_POINT_2F* rotationPoint, D2D1_POINT_2F* destOffset, D2D1_POINT_2F* scaleFlip, D2D1_POINT_2F* newRotationPoint);

			/// <summary>	Sets up the draw frame center rotated and its effects. </summary>
			///
			/// <remarks>	Tobias, 26.05.2015. </remarks>
			///
			/// <param name="drawRect">			  	[in] The draw rectangle. </param>
			/// <param name="scale">			  	[in] The scale. </param>
			/// <param name="color">			  	[in] The color. </param>
			/// <param name="rotateDegree">		  	[in] The rotate degree. </param>
			/// <param name="flipMode">			  	[in] The flip mode. </param>
			/// <param name="interpolationLinear">	[in] The interpolation linear. </param>
			///
			/// <returns>	The destination Offset. </returns>
			D2D1_POINT_2F SetupDrawFrameCenterRotated(const D2D1_RECT_F& drawRect, const D2D1_POINT_2F& scale, const D2D1::ColorF& color, const float& rotateDegree, const SPRITE_FLIP_MODE& flipMode, const SPRITE_INTERPOLATION_MODE& interpolationMode);
			/// <summary>	Sets up the draw frame point rotated and its effects. </summary>
			///
			/// <remarks>	Tobias, 26.05.2015. </remarks>
			///
			/// <param name="drawRect">			  	[in] The draw rectangle. </param>
			/// <param name="scale">			  	[in] The scale. </param>
			/// <param name="color">			  	[in] The color. </param>
			/// <param name="rotateDegree">		  	[in] The rotate degree. </param>
			/// <param name="rotatePoint">		  	[in] The rotate point. </param>
			/// <param name="flipMode">			  	[in] The flip mode. </param>
			/// <param name="interpolationLinear">	[in] The interpolation linear. </param>
			///
			/// <returns>	The destination Offset. </returns>
			D2D1_POINT_2F SetupDrawFramePointRotated(const D2D1_RECT_F& drawRect, const D2D1_POINT_2F& scale, const D2D1::ColorF& color, const float& rotateDegree, const D2D1_POINT_2F& rotatePoint, const SPRITE_FLIP_MODE& flipMode, const SPRITE_INTERPOLATION_MODE& interpolationMode);
		};
	}
}

