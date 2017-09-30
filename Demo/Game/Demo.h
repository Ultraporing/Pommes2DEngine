//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include "P2DE\GFX\Camera.h"
#include <P2DE\Game\BaseGame.h>

namespace Demo
{
	class Demo : public P2DE::GAME::BaseGame
	{
		private:
			HWND m_hWndGamewindow;
			//P2DE::GFX::Camera m_Camera;

		public:
		Demo() {};
			Demo(HWND hWndGamewindow);
			~Demo();

			bool LoadResources() override;
			bool UnloadResources(bool isGameEnd) override;

			void Render();
			// if returns TRUE signal gameloop to stop
			bool Update(const float& deltaTime); 
	};
}

