#include "FTGame.h"
#include <sstream>
#include <P2DE\GFX\Graphics.h>
#include <P2DE\Utilities\ComPtr.h>

namespace FTGame
{
	P2DE::UTILITIES::ComPtr<ID2D1Effect> colorMatrixFx;

	FTGame::FTGame(P2DE::GFX::Graphics* gfx, HWND hWndGamewindow)
	{
		m_Graphics = NULL;
		m_Graphics = gfx;
		m_Camera = P2DE::GFX::Camera(gfx);
		m_hWndGamewindow = hWndGamewindow;
		m_Graphics->SetCurrentGame(this);

		LoadResources();
	}

	FTGame::~FTGame()
	{
		UnloadResources();
		m_Graphics = NULL;
	}

	bool FTGame::LoadResources()
	{
		if (m_Graphics->LoadBitmapFromFile(L"av.png", &testbmp))
		{
			if (m_Graphics->CreateBitmapTintEffect(&colorMatrixFx, testbmp, 1.0f, 0, 1.0f))
				return true;
		}
		
		return false;
	}

	bool FTGame::UnloadResources()
	{
		if (testbmp)
		{
			testbmp->Release();
			testbmp = NULL;
		}

		if (colorMatrixFx)
			colorMatrixFx.~ComPtr();

		return true;
	}

	void FTGame::Render()
	{
		if (!m_Graphics->CanDraw())
			return;

		m_Graphics->BeginDraw();
		m_Graphics->ClearScreen(0.0f, 0.0f, 0.5f);

		m_Graphics->DrawFilledCircle(0, 0, 100, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f);
		
		m_Graphics->SetBitmapTintEffectColor(colorMatrixFx, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);
		m_Graphics->DrawEffect(colorMatrixFx, D2D1::Point2F(50, 50));

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

		if (m_InputManager.IsKeyPressed(VK_KEY_D))
		{
			m_Graphics->SetGameWindowSize(RECT() = { 0, 0, 1024, 768 });
			m_Graphics->SetGameWindowPos(POINT() = { 0, 0 });
		}

		return false;
	}
}
