//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include "P2DE\GFX\Camera.h"
#include "P2DE\Input\InputManager.h"

namespace P2DE
{
	namespace GFX
	{
		class Graphics;
	}
}

namespace FTGame
{
	class FTGame
	{
		private:
			HWND m_hWndGamewindow;

			P2DE::GFX::Graphics* m_Graphics;
			P2DE::GFX::Camera m_Camera;
			P2DE::INPUT::InputManager m_InputManager;

			ID2D1Bitmap* testbmp;

		public:
			FTGame(P2DE::GFX::Graphics* gfx, HWND hWndGamewindow);
			~FTGame();

			P2DE::INPUT::InputManager* GetInputManager() { return &m_InputManager; }

			void Render();
			// if returns TRUE signal gameloop to stop
			bool Update(const float& deltaTime); 
	};
}

