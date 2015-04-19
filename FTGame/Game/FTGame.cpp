#include "FTGame.h"
#include "P2DE\GFX\Graphics.h"
#include <sstream>

namespace FTGame
{
	FTGame::FTGame(P2DE::GFX::Graphics* gfx, HWND hWndGamewindow)
	{
		m_Graphics = NULL;
		m_Graphics = gfx;
		m_Camera = P2DE::GFX::Camera(gfx);
		m_hWndGamewindow = hWndGamewindow;
		
		m_Graphics->LoadBitmapFromFile(L"av.png", &testbmp);
	}

	FTGame::~FTGame()
	{
		m_Graphics = NULL;
		testbmp->Release();
	}

	void FTGame::Render()
	{
		m_Graphics->BeginDraw();
		m_Graphics->ClearScreen(0.0f, 0.0f, 0.5f);

		m_Graphics->DrawCircle(0, 0, 100, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f);

		m_Graphics->DrawBitmap(testbmp, 50, 50, testbmp->GetSize().width / 2, testbmp->GetSize().height / 2, 0, 0, testbmp->GetSize().width / 2, testbmp->GetSize().height / 2, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

		m_Graphics->EndDraw();
	}

	bool FTGame::Update(const float& deltaTime)
	{
		int cameraSpeed = 50;

		D2D1_POINT_2F camMoveAmount = D2D1::Point2F();

		if (m_InputManager.IsKeyDown(VK_RIGHT))
			camMoveAmount.x = cameraSpeed * deltaTime;
		else if (m_InputManager.IsKeyDown(VK_LEFT))
			camMoveAmount.x = -cameraSpeed * deltaTime;

		if (m_InputManager.IsKeyDown(VK_UP))
			camMoveAmount.y = -cameraSpeed * deltaTime;
		else if (m_InputManager.IsKeyDown(VK_DOWN))
			camMoveAmount.y = cameraSpeed * deltaTime;

		m_Camera.MoveCamera(camMoveAmount);

		if (m_InputManager.IsKeyPressed(VK_ESCAPE))
			return true;

		POINT p = POINT();
		if (m_InputManager.IsKeyPressed(VK_SPACE))
		{
			
			bool ret = m_InputManager.GetGameMousePos(m_hWndGamewindow, &p, &m_Camera);
			if (ret)
			{
				std::wstringstream s;
				s << L"x = " << p.x << L", y = " << p.y;
				MessageBox(NULL, s.str().c_str(), L"merp", MB_OK);
			}
			else
				MessageBox(NULL, L"fail", L"merp", MB_OK);
		}

		return false;
	}
}
