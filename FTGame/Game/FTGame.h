//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once
#include "P2DE\GFX\Camera.h"
#include <P2DE\Game\BaseGame.h>

namespace P2DE
{
	namespace GFX
	{
		class Graphics;
	}
}

namespace FTGame
{
	class FTGame : public P2DE::GAME::BaseGame
	{
		private:
			HWND m_hWndGamewindow;

			P2DE::GFX::Graphics* m_Graphics;
			P2DE::GFX::Camera m_Camera;

			bool LoadResources() override;
			bool UnloadResources() override;

		public:
			FTGame(P2DE::GFX::Graphics* gfx, HWND hWndGamewindow);
			~FTGame();

			void Render();
			// if returns TRUE signal gameloop to stop
			bool Update(const float& deltaTime); 
	};
}

