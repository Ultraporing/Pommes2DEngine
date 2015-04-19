//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include <d2d1_1helper.h>

namespace P2DE
{
	namespace GFX
	{
		class Graphics;

		class Camera
		{
			private:
			P2DE::GFX::Graphics* m_Graphics;
			D2D1_POINT_2F m_CameraPos;

			public:
			Camera();
			Camera(P2DE::GFX::Graphics* gfx);
			~Camera();

			D2D1_POINT_2F GetCameraPos() { return m_CameraPos; }
			void SetCameraPos(D2D1_POINT_2F newPos);
			void MoveCamera(D2D1_POINT_2F delta);
		};
	}
}

