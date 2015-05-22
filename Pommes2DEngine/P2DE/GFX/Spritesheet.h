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

struct ID2D1Bitmap;
struct ID2D1Image;
struct ID2D1Effect;

namespace P2DE
{
	namespace GFX
	{
		class Graphics;

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
			/// <summary>	The scale effect used for drawing the frames. </summary>
			ID2D1Effect* m_ScaleFx;
			/// <summary>	The intermediate output image. </summary>
			ID2D1Image* m_IntermediateOutputImage;
			/// <summary>	Information describing the spritesheet. </summary>
			SpritesheetInfo m_SpritesheetInfo;
			/// <summary>	The spritesheet bitmap. </summary>
			ID2D1Bitmap* m_SpritesheetBitmap;

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
			/// <param name="pathToSpritesheetInfoTXT">	The path to spritesheet information text. </param>
			/// <param name="graphics">				   	[in,out] If non-null, the graphics class to be used. Sets m_Graphics to this parameter. </param>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool LoadSpritesheet(const std::wstring& pathToSpritesheetInfoTXT, P2DE::GFX::Graphics* graphics);

			/// <summary>	Unloads the spritesheet bitmap. Mostly used if we have to resize the Swapchain. </summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool UnloadSpritesheetBitmap();

			/// <summary>	Draws a frame of the spritesheet by use of the frameId. </summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <param name="dest">   	Destination for the frame. </param>
			/// <param name="frameId">	Identifier for the frame. </param>
			/// <param name="scale">	Scale for the frame. </param>
			/// <param name="color">	Color tint for the frame. </param>
			/// <param name="interpolationLinear">	If TRUE Linear Interpolation is used, otherwise Nearest Neighbor. </param>
			void DrawFrame(D2D1_POINT_2F dest, unsigned int frameId, D2D1_POINT_2F scale = { 1.0f, 1.0f }, D2D1::ColorF color = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), bool interpolationLinear = true);	
			
			/// <summary>	Draws a frame of the spritesheet by use of an source Rectangle. </summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <param name="dest">   	Destination for the frame. </param>
			/// <param name="source">	Source rectangle of the frame. Rect: left = x, top = y, right = width, bottom = height </param>
			/// <param name="scale">	Scale for the frame. </param>
			/// <param name="color">	Color tint for the frame. </param>
			/// <param name="interpolationLinear">	If TRUE Linear Interpolation is used, otherwise Nearest Neighbor. </param>
			void DrawFrame(D2D1_POINT_2F dest, D2D1_RECT_F source, D2D1_POINT_2F scale = { 1.0f, 1.0f }, D2D1::ColorF color = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), bool interpolationLinear = true);

			private:
			/// <summary>	Reload the spritesheet bitmap. Mostly used after unloading the spritesheet bitmap. </summary>
			///
			/// <remarks>	Tobias, 18.05.2015. </remarks>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			bool ReloadSpritesheetBitmap();
		};
	}
}

