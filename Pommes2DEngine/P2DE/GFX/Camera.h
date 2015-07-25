//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#ifndef CAMERA_H
	#define CAMERA_H
	#ifdef _WIN32
		#include <d2d1_1helper.h>
	#elif __APPLE__
		// TODO: Mac Headers
	#endif

	namespace P2DE
	{
		namespace GFX
		{
			class Graphics;
			/// <summary>	A basic 2D Camera. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			class Camera
			{
				#ifdef _WIN32
					private:
					/// <summary>	The graphics class used. </summary>
					P2DE::GFX::Graphics* m_Graphics;
					/// <summary>	The camera position. </summary>
					D2D1_POINT_2F m_CameraPos;

					public:
					/// <summary>	Default constructor. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					Camera();
					/// <summary>	Constructor. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="gfx">	[in,out] If non-null, the graphics. </param>
					Camera(P2DE::GFX::Graphics* gfx);
					/// <summary>	Destructor. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					~Camera();

					/// <summary>	Gets camera position. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <returns>	The camera position. </returns>
					D2D1_POINT_2F GetCameraPos() { return m_CameraPos; }
					/// <summary>	Sets camera position. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="newPos">	The new position. </param>
					void SetCameraPos(D2D1_POINT_2F newPos);

					/// <summary>	Move camera. </summary>
					///
					/// <remarks>	Tobias, 22.05.2015. </remarks>
					///
					/// <param name="delta">	The delta. </param>
					void MoveCamera(D2D1_POINT_2F delta);
				#elif __APPLE__
					// TODO: Mac Code
				#endif
			};
		}
	}
#endif