#include "FTGame.h"
#include <sstream>
#include <P2DE\GFX\Graphics.h>
#include <P2DE\Utilities\ComPtr.h>
#include "P2DE\GFX\SpritesheetAtlas.h"
#include "P2DE\Input\InputManager.h"

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
		m_GameCrashed = false;

		m_GameCrashed = !LoadResources();
		P2DE::INPUT::InputManager::InitXboxControllers();
	}

	FTGame::~FTGame()
	{
		UnloadResources(true);
		m_Graphics = NULL;
	}

	bool FTGame::LoadResources()
	{	
		if (!P2DE::GFX::SpritesheetAtlas::AddLoadSpritesheet(L"Assets\\Graphics\\Spritesheets\\roguelikeSheet_transparent_Info.txt", m_Graphics))
			return false;
		
		return true;
	}

	bool FTGame::UnloadResources(bool isGameEnd)
	{
		if (colorMatrixFx)
			colorMatrixFx.~ComPtr();

		if (!isGameEnd)
			P2DE::GFX::SpritesheetAtlas::UnloadSpritesheetBitmaps();
		else
			P2DE::GFX::SpritesheetAtlas::ShutdownAtlas();

		return true;
	}

	static float scale = 1.0f;
	static D2D1::ColorF color = { 1.0f, 1.0f, 1.0f };
	static float rotation = 0.0f;
	static int flip = P2DE::GFX::SPRITE_FLIP_MODE::NONE;

	static P2DE::GFX::ImagePropertiesI test1 = P2DE::GFX::ImagePropertiesI();
	static P2DE::GFX::ImagePropertiesR test2 = P2DE::GFX::ImagePropertiesR();
	static P2DE::GFX::ImagePropertiesR test3 = P2DE::GFX::ImagePropertiesR();

	void FTGame::Render()
	{
		if (!m_Graphics->CanDraw())
			return;

		m_Graphics->BeginDraw();
		m_Graphics->ClearScreen(0.0f, 0.0f, 0.5f);

		m_Graphics->DrawFilledCircle(0, 0, 100, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f);

		test1 = P2DE::GFX::ImagePropertiesI(L"roguelikeSheet", 70, D2D1::Point2F(2.0f, 2.0f), D2D1::ColorF(color), 90.0f, true, D2D1::Point2F(), (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);
		P2DE::GFX::SpritesheetAtlas::DrawFrame(D2D1::Point2F(200, 200), &test1);

		test2 = P2DE::GFX::ImagePropertiesR(L"roguelikeSheet", D2D1::RectF(16, 102, 32, 16), D2D1::Point2F(5.0f, 5.0f), D2D1::ColorF::White, rotation, false, D2D1::Point2F(8, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);
		P2DE::GFX::SpritesheetAtlas::DrawFrame(D2D1::Point2F(300, 200), &test2);

		test3 = P2DE::GFX::ImagePropertiesR(L"roguelikeSheet", D2D1::RectF(0, 102, 16, 16), D2D1::Point2F(5.0f, 5.0f), D2D1::ColorF::White, rotation, false, D2D1::Point2F(8, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);
		P2DE::GFX::SpritesheetAtlas::DrawFrame(D2D1::Point2F(300, 100), &test3);
		
		//sheet.DrawFrameCenterRotated(D2D1::Point2F(100, 100), 2, D2D1::Point2F(scale, scale), D2D1::ColorF(1.0f, 1.0f, 1.0f), rotation, (P2DE::GFX::SPRITE_FLIP_MODE)flip, false);
		//sheet.DrawFramePointRotated(D2D1::Point2F(200, 100), 2, D2D1::Point2F(2.0f, 2.0f), D2D1::ColorF(color), rotation, D2D1::Point2F(0, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, false);

		//sheet.DrawFramePointRotated(D2D1::Point2F(100, 200), 70, D2D1::Point2F(scale, scale), D2D1::ColorF(1.0f, 1.0f, 1.0f), -90.0f, D2D1::Point2F(0, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, true);
//		P2DE::GFX::SpritesheetAtlas::GetSpritesheet(L"roguelikeSheet")->DrawFrameCenterRotated(D2D1::Point2F(200, 200), 70, D2D1::Point2F(2.0f, 2.0f), D2D1::ColorF(color), 90.0f, (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);

//		P2DE::GFX::SpritesheetAtlas::GetSpritesheet(L"roguelikeSheet")->DrawFramePointRotated(D2D1::Point2F(300, 200), D2D1::RectF(16, 102, 32, 16), D2D1::Point2F(5.0f, 5.0f), D2D1::ColorF::White, rotation, D2D1::Point2F(8, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);

//		P2DE::GFX::SpritesheetAtlas::GetSpritesheet(L"roguelikeSheet")->DrawFramePointRotated(D2D1::Point2F(300, 100), D2D1::RectF(0, 102, 16, 16), D2D1::Point2F(5.0f, 5.0f), D2D1::ColorF::White, rotation, D2D1::Point2F(8, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);

		m_Graphics->EndDraw();
	}

	bool FTGame::Update(const float& deltaTime)
	{
		int cameraSpeed = 50;

		D2D1_POINT_2F camMoveAmount = D2D1::Point2F();
		
		if (P2DE::INPUT::InputManager::IsKeyDown(VK_RIGHT))
			camMoveAmount.x = cameraSpeed * deltaTime;
		else if (P2DE::INPUT::InputManager::IsKeyDown(VK_LEFT))
			camMoveAmount.x = -cameraSpeed * deltaTime;

		if (P2DE::INPUT::InputManager::IsKeyDown(VK_UP))
			camMoveAmount.y = -cameraSpeed * deltaTime;
		else if (P2DE::INPUT::InputManager::IsKeyDown(VK_DOWN))
			camMoveAmount.y = cameraSpeed * deltaTime;

		m_Camera.MoveCamera(camMoveAmount);

		if (P2DE::INPUT::InputManager::IsKeyPressed(VK_ESCAPE))
			return true;

		POINT p = POINT();
		if (P2DE::INPUT::InputManager::IsKeyPressed(VK_SPACE))
		{
			
			bool ret = P2DE::INPUT::InputManager::GetGameMousePos(m_hWndGamewindow, &p, &m_Camera);
			if (ret)
			{
				std::wstringstream s;
				s << L"x = " << p.x << L", y = " << p.y;
				MessageBox(NULL, s.str().c_str(), L"merp", MB_OK);
			}
			else
				MessageBox(NULL, L"fail", L"merp", MB_OK);
		}

		if (P2DE::INPUT::InputManager::IsKeyDown(VK_KEY_A))
		{
			rotation -= 1.0f;
			if (rotation < 0.0f)
				rotation = 360.0f;
		}

		if (P2DE::INPUT::InputManager::IsKeyDown(VK_KEY_S))
		{
			rotation += 1.0f;
			if (rotation > 360.0f)
				rotation = 0;
		}

		if (P2DE::INPUT::InputManager::IsKeyPressed(VK_KEY_D))
		{
			m_Graphics->SetGameWindowSize(RECT() = { 0, 0, 1024, 768 });
			m_Graphics->SetGameWindowPos(POINT() = { 0, 0 });
		}

		if (P2DE::INPUT::InputManager::IsKeyPressed(VK_KEY_X))
		{
			flip |= P2DE::GFX::SPRITE_FLIP_MODE::HORIZONTAL;
		}

		if (P2DE::INPUT::InputManager::IsKeyPressed(VK_KEY_C))
		{
			flip |= P2DE::GFX::SPRITE_FLIP_MODE::VERTICAL;
		}

		if (P2DE::INPUT::InputManager::IsKeyPressed(VK_KEY_V))
		{
			flip = P2DE::GFX::SPRITE_FLIP_MODE::NONE;
		}

		if (P2DE::INPUT::InputManager::IsMousewheelScrollUp())
		{
			std::wstringstream s;
			s << L"MousewheelState: " << P2DE::INPUT::InputManager::GetMousewheelState();
			MessageBox(NULL, s.str().c_str(), L"mouseWheelUP", MB_OK);
		}
		
		if (P2DE::INPUT::InputManager::IsMousewheelScrollDown())
		{
			std::wstringstream s;
			s << L"MousewheelState: " << P2DE::INPUT::InputManager::GetMousewheelState();
			MessageBox(NULL, s.str().c_str(), L"mouseWheelDOWN", MB_OK);
		}

		if (P2DE::INPUT::InputManager::IsControllerConnected(1))
		{
			if (P2DE::INPUT::InputManager::IsControllerButtonPressed(1, XINPUT_GAMEPAD_X))
			{
				P2DE::INPUT::InputManager::GetController(1)->Vibrate(65535, 0);
			}

			if (P2DE::INPUT::InputManager::IsControllerButtonPressed(1, XINPUT_GAMEPAD_B))
			{
				P2DE::INPUT::InputManager::GetController(1)->Vibrate(0, 65535);
			}

			if (P2DE::INPUT::InputManager::IsControllerButtonPressed(1, XINPUT_GAMEPAD_Y))
			{
				P2DE::INPUT::InputManager::GetController(1)->Vibrate(65535, 65535);
			}

			if (P2DE::INPUT::InputManager::IsControllerButtonPressed(1, XINPUT_GAMEPAD_A))
			{
				P2DE::INPUT::InputManager::GetController(1)->Vibrate(0, 0);
			}
		}

		P2DE::INPUT::InputManager::ResetMousewheelState();

		return false;
	}
}
