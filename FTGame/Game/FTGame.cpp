#include "FTGame.h"
#include <sstream>
#include <P2DE\GFX\Graphics.h>
#include <P2DE\Utilities\ComPtr.h>
#include "P2DE\GFX\Spritesheet.h"

namespace FTGame
{
	P2DE::UTILITIES::ComPtr<ID2D1Effect> colorMatrixFx;
	P2DE::GFX::Spritesheet sheet;

	FTGame::FTGame(P2DE::GFX::Graphics* gfx, HWND hWndGamewindow)
	{
		m_Graphics = NULL;
		m_Graphics = gfx;
		m_Camera = P2DE::GFX::Camera(gfx);
		m_hWndGamewindow = hWndGamewindow;
		m_Graphics->SetCurrentGame(this);
		m_GameCrashed = false;

		m_GameCrashed = !LoadResources();
	}

	FTGame::~FTGame()
	{
		UnloadResources();
		m_Graphics = NULL;
	}

	bool FTGame::LoadResources()
	{
		if (!sheet.LoadSpritesheet(L"Assets\\Graphics\\Spritesheets\\roguelikeSheet_transparent_Info.txt", m_Graphics))
			return false;
		
		return true;
	}

	bool FTGame::UnloadResources()
	{
		if (colorMatrixFx)
			colorMatrixFx.~ComPtr();

		sheet.UnloadSpritesheetBitmap();

		return true;
	}

	static float scale = 1.0f;
	static D2D1::ColorF color = { 1.0f, 1.0f, 1.0f };
	static float rotation = 0.0f;
	static int flip = P2DE::GFX::SPRITE_FLIP_MODE::NONE;

	void FTGame::Render()
	{
		if (!m_Graphics->CanDraw())
			return;

		m_Graphics->BeginDraw();
		m_Graphics->ClearScreen(0.0f, 0.0f, 0.5f);

		m_Graphics->DrawFilledCircle(0, 0, 100, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f);

		//sheet.DrawFrameCenterRotated(D2D1::Point2F(100, 100), 2, D2D1::Point2F(scale, scale), D2D1::ColorF(1.0f, 1.0f, 1.0f), rotation, (P2DE::GFX::SPRITE_FLIP_MODE)flip, false);
		//sheet.DrawFramePointRotated(D2D1::Point2F(200, 100), 2, D2D1::Point2F(2.0f, 2.0f), D2D1::ColorF(color), rotation, D2D1::Point2F(0, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, false);

		//sheet.DrawFramePointRotated(D2D1::Point2F(100, 200), 70, D2D1::Point2F(scale, scale), D2D1::ColorF(1.0f, 1.0f, 1.0f), -90.0f, D2D1::Point2F(0, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, true);
		sheet.DrawFrameCenterRotated(D2D1::Point2F(200, 200), 70, D2D1::Point2F(2.0f, 2.0f), D2D1::ColorF(color), 90.0f, (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);

		sheet.DrawFramePointRotated(D2D1::Point2F(300, 100), D2D1::RectF(0, 102, 16, 16), D2D1::Point2F(5.0f, 5.0f), D2D1::ColorF::White, rotation, D2D1::Point2F(8, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);

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

		if (m_InputManager.IsKeyDown(VK_KEY_A))
		{
			rotation -= 1.0f;
			if (rotation < 0.0f)
				rotation = 360.0f;
		}

		if (m_InputManager.IsKeyDown(VK_KEY_S))
		{
			rotation += 1.0f;
			if (rotation > 360.0f)
				rotation = 0;
		}

		if (m_InputManager.IsKeyPressed(VK_KEY_D))
		{
			m_Graphics->SetGameWindowSize(RECT() = { 0, 0, 1024, 768 });
			m_Graphics->SetGameWindowPos(POINT() = { 0, 0 });
		}

		if (m_InputManager.IsKeyPressed(VK_KEY_X))
		{
			flip |= P2DE::GFX::SPRITE_FLIP_MODE::HORIZONTAL;
		}

		if (m_InputManager.IsKeyPressed(VK_KEY_C))
		{
			flip |= P2DE::GFX::SPRITE_FLIP_MODE::VERTICAL;
		}

		if (m_InputManager.IsKeyPressed(VK_KEY_V))
		{
			flip = P2DE::GFX::SPRITE_FLIP_MODE::NONE;
		}

		return false;
	}
}
