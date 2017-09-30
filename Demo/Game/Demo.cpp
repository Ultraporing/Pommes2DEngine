#include "Demo.h"
#include <sstream>
#include <P2DE\GFX\Graphics.h>
#include <P2DE\Utilities\ComPtr.h>
//#include <P2DE\GFX\SpritesheetAtlas.h>
#include <P2DE\Input\InputManager.h>
#include <P2DE\FileIO\FileIO.h>
#include <P2DE\SFX\SoundManager.h>
#include <P2DE\SFX\P2DE_Sound.h>

namespace Demo
{
	Demo::Demo(HWND hWndGamewindow)
	{
		//m_Camera = P2DE::GFX::Camera();
		m_hWndGamewindow = hWndGamewindow;
		P2DE_GFX.SetCurrentGame(this);
		m_GameCrashed = false;
		
		m_GameCrashed = !LoadResources();
		P2DE_INPUT.InitXboxControllers();
	}

	P2DE::SFX::P2DE_Sound sound;

	Demo::~Demo()
	{
		P2DE_GFX.UnloadDirectX(true);
	}

	bool Demo::LoadResources()
	{	
		//if (!P2DE::GFX::SpritesheetAtlas::AddLoadSpritesheet(L"Assets\\Graphics\\Spritesheets\\roguelikeSheet_transparent_Info.txt", m_Graphics))
		//	return false;

		if (!P2DE_SFX.CreateSound(L"pew", L"Assets\\Sound\\Fx\\pew.wav"))
			return false;
	//	else
		//	sound.setBuffer(buffer);

		//if (!music.openFromFile("Assets\\Sound\\Music\\Dragonforce-Through the Fire and Flames Full Version.ogg"))
			//return false;
		
		P2DE_GFX.LoadShaders();

		return true;
	}

	bool Demo::UnloadResources(bool isGameEnd)
	{
		//if (colorMatrixFx)
		//	colorMatrixFx.~ComPtr();
/*
		if (!isGameEnd)
			P2DE::GFX::SpritesheetAtlas::UnloadSpritesheetBitmaps();
		else
			P2DE::GFX::SpritesheetAtlas::ShutdownAtlas();
			*/

		P2DE_GFX.UnloadShaders();

		return true;
	}

	static float scale = 1.0f;
	static D2D1::ColorF color = { 1.0f, 1.0f, 1.0f };
	static float rotation = 0.0f;
	//static int flip = P2DE::GFX::SPRITE_FLIP_MODE::NONE;
	/*
	static P2DE::GFX::ImageProperties test1 = P2DE::GFX::ImageProperties(L"roguelikeSheet", 70, D2D1::RectF(0, 0, 0,0), D2D1::Point2F(2.0f, 2.0f), D2D1::ColorF(color), 90.0f, true, D2D1::Point2F(), (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);
	static P2DE::GFX::ImageProperties test2 = P2DE::GFX::ImageProperties(L"roguelikeSheet", 0, D2D1::RectF(16, 102, 32, 16), D2D1::Point2F(5.0f, 5.0f), D2D1::ColorF::White, rotation, false, D2D1::Point2F(8, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);
	static P2DE::GFX::ImageProperties test3 = P2DE::GFX::ImageProperties(L"roguelikeSheet", 0, D2D1::RectF(0, 102, 16, 16), D2D1::Point2F(5.0f, 5.0f), D2D1::ColorF::White, rotation, false, D2D1::Point2F(8, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);

	static P2DE::GFX::ImageProperties testRead = P2DE::GFX::ImageProperties();
	*/
	static std::vector<byte> testData;

	void Demo::Render()
	{
		if (!P2DE_GFX.CanDraw())
			return;

		P2DE_GFX.BeginDraw();
		P2DE_GFX.ClearScreen(0.0f, 0.2f, 0.4f);
		P2DE_GFX.RenderDrawable();

		//m_Graphics->DrawFilledCircle(0, 0, 100, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f);
		/*
		P2DE::GFX::SpritesheetAtlas::DrawFrame(D2D1::Point2F(200, 200), &test1);
		P2DE::GFX::SpritesheetAtlas::DrawFrame(D2D1::Point2F(300, 200), &test2);
		P2DE::GFX::SpritesheetAtlas::DrawFrame(D2D1::Point2F(300, 100), &test3);
		*/
		//sheet.DrawFrameCenterRotated(D2D1::Point2F(100, 100), 2, D2D1::Point2F(scale, scale), D2D1::ColorF(1.0f, 1.0f, 1.0f), rotation, (P2DE::GFX::SPRITE_FLIP_MODE)flip, false);
		//sheet.DrawFramePointRotated(D2D1::Point2F(200, 100), 2, D2D1::Point2F(2.0f, 2.0f), D2D1::ColorF(color), rotation, D2D1::Point2F(0, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, false);

		//sheet.DrawFramePointRotated(D2D1::Point2F(100, 200), 70, D2D1::Point2F(scale, scale), D2D1::ColorF(1.0f, 1.0f, 1.0f), -90.0f, D2D1::Point2F(0, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, true);
//		P2DE::GFX::SpritesheetAtlas::GetSpritesheet(L"roguelikeSheet")->DrawFrameCenterRotated(D2D1::Point2F(200, 200), 70, D2D1::Point2F(2.0f, 2.0f), D2D1::ColorF(color), 90.0f, (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);

//		P2DE::GFX::SpritesheetAtlas::GetSpritesheet(L"roguelikeSheet")->DrawFramePointRotated(D2D1::Point2F(300, 200), D2D1::RectF(16, 102, 32, 16), D2D1::Point2F(5.0f, 5.0f), D2D1::ColorF::White, rotation, D2D1::Point2F(8, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);

//		P2DE::GFX::SpritesheetAtlas::GetSpritesheet(L"roguelikeSheet")->DrawFramePointRotated(D2D1::Point2F(300, 100), D2D1::RectF(0, 102, 16, 16), D2D1::Point2F(5.0f, 5.0f), D2D1::ColorF::White, rotation, D2D1::Point2F(8, 0), (P2DE::GFX::SPRITE_FLIP_MODE)flip, P2DE::GFX::SPRITE_INTERPOLATION_MODE::NEAREST_NEIGHBOR);

		P2DE_GFX.EndDraw();
	}

	bool Demo::Update(const float& deltaTime)
	{
		int cameraSpeed = 50;

		D2D1_POINT_2F camMoveAmount = D2D1::Point2F();
		
		if (P2DE_INPUT.IsKeyDown(VK_RIGHT))
			camMoveAmount.x = cameraSpeed * deltaTime;
		else if (P2DE_INPUT.IsKeyDown(VK_LEFT))
			camMoveAmount.x = -cameraSpeed * deltaTime;

		if (P2DE_INPUT.IsKeyDown(VK_UP))
			camMoveAmount.y = -cameraSpeed * deltaTime;
		else if (P2DE_INPUT.IsKeyDown(VK_DOWN))
			camMoveAmount.y = cameraSpeed * deltaTime;

		//m_Camera.MoveCamera(camMoveAmount);

		if (P2DE_INPUT.IsKeyPressed(VK_ESCAPE))
			return true;

		POINT p = POINT();
		/*
		if (P2DE_INPUT.IsKeyPressed(VK_SPACE))
		{
			
			bool ret = P2DE_INPUT.GetGameMousePos(m_hWndGamewindow, &p, &m_Camera);
			if (ret)
			{
				std::wstringstream s;
				s << L"x = " << p.x << L", y = " << p.y;
				MessageBox(NULL, s.str().c_str(), L"merp", MB_OK);
			}
			else
				MessageBox(NULL, L"fail", L"merp", MB_OK);
		}*/
		/*
		if (P2DE_INPUT.IsKeyDown(VK_KEY_A))
		{
			rotation -= 1.0f;
			if (rotation < 0.0f)
				rotation = 360.0f;

			test1.m_RotateDegree = rotation;
			test2.m_RotateDegree = rotation;
			test3.m_RotateDegree = rotation;
		}

		if (P2DE_INPUT.IsKeyDown(VK_KEY_S))
		{
			rotation += 1.0f;
			if (rotation > 360.0f)
				rotation = 0;

			test1.m_RotateDegree = rotation;
			test2.m_RotateDegree = rotation;
			test3.m_RotateDegree = rotation;
		}
		*/
		if (P2DE_INPUT.IsKeyPressed(VK_KEY_D))
		{
			P2DE_GFX.SetGameWindowSize(RECT() = { 0, 0, 1024, 768 });
			P2DE_GFX.SetGameWindowPos(POINT() = { 0, 0 });
		}
		/*
		if (P2DE_INPUT.IsKeyPressed(VK_KEY_X))
		{
			flip |= P2DE::GFX::SPRITE_FLIP_MODE::HORIZONTAL;

			test1.m_FlipMode = (P2DE::GFX::SPRITE_FLIP_MODE)flip;
			test2.m_FlipMode = (P2DE::GFX::SPRITE_FLIP_MODE)flip;
			test3.m_FlipMode = (P2DE::GFX::SPRITE_FLIP_MODE)flip;
		}

		if (P2DE_INPUT.IsKeyPressed(VK_KEY_C))
		{
			flip |= P2DE::GFX::SPRITE_FLIP_MODE::VERTICAL;

			test1.m_FlipMode = (P2DE::GFX::SPRITE_FLIP_MODE)flip;
			test2.m_FlipMode = (P2DE::GFX::SPRITE_FLIP_MODE)flip;
			test3.m_FlipMode = (P2DE::GFX::SPRITE_FLIP_MODE)flip;
		}

		if (P2DE_INPUT.IsKeyPressed(VK_KEY_V))
		{
			flip = P2DE::GFX::SPRITE_FLIP_MODE::NONE;

			test1.m_FlipMode = (P2DE::GFX::SPRITE_FLIP_MODE)flip;
			test2.m_FlipMode = (P2DE::GFX::SPRITE_FLIP_MODE)flip;
			test3.m_FlipMode = (P2DE::GFX::SPRITE_FLIP_MODE)flip;
		}
		*/
		if (P2DE_INPUT.IsMousewheelScrollUp())
		{
			std::wstringstream s;
			s << L"MousewheelState: " << P2DE_INPUT.GetMousewheelState();
			MessageBox(NULL, s.str().c_str(), L"mouseWheelUP", MB_OK);
		}
		
		if (P2DE_INPUT.IsMousewheelScrollDown())
		{
			std::wstringstream s;
			s << L"MousewheelState: " << P2DE_INPUT.GetMousewheelState();
			MessageBox(NULL, s.str().c_str(), L"mouseWheelDOWN", MB_OK);
		}

		if (P2DE_INPUT.IsControllerConnected(1))
		{
			if (P2DE_INPUT.IsControllerButtonPressed(1, XINPUT_GAMEPAD_X))
			{
				P2DE_INPUT.GetController(1)->Vibrate(65535, 0);
			}

			if (P2DE_INPUT.IsControllerButtonPressed(1, XINPUT_GAMEPAD_B))
			{
				P2DE_INPUT.GetController(1)->Vibrate(0, 65535);
			}

			if (P2DE_INPUT.IsControllerButtonPressed(1, XINPUT_GAMEPAD_Y))
			{
				P2DE_INPUT.GetController(1)->Vibrate(65535, 65535);
			}

			if (P2DE_INPUT.IsControllerButtonPressed(1, XINPUT_GAMEPAD_A))
			{
				P2DE_INPUT.GetController(1)->Vibrate(0, 0);
			}
		}
		/*
		if (P2DE_INPUT.IsKeyPressed(VK_KEY_6))
		{
			P2DE::GFX::ImageProperties blerg2 = test1;
			blerg2.m_Color = D2D1::ColorF(D2D1::ColorF::BlueViolet);
			blerg2.WriteToBinary(&testData);
			P2DE::FILEIO::FileIO::SaveBinaryFile(L"testData.bin", &testData);
			testData.clear();
		}

		if (P2DE_INPUT.IsKeyPressed(VK_KEY_7))
		{
			P2DE::FILEIO::FileIO::ReadBinaryFile(L"testData.bin", &testData);
			P2DE::GFX::ImageProperties::ReadFromBinary(&testData, &testData.begin(), NULL, test1);
		}

		if (P2DE_INPUT.IsKeyPressed(VK_KEY_4))
		{
			std::vector<P2DE::GFX::ImageProperties> vec;

			P2DE::GFX::ImageProperties blerg2 = test1;
			blerg2.m_Color = D2D1::ColorF(D2D1::ColorF::Crimson);
			vec.push_back(blerg2);

			blerg2 = test2;
			blerg2.m_Color = D2D1::ColorF(D2D1::ColorF::MediumBlue);
			vec.push_back(blerg2);

			blerg2 = test3;
			blerg2.m_Color = D2D1::ColorF(D2D1::ColorF::Crimson);
			vec.push_back(blerg2);
			

			P2DE::GFX::ImageProperties::WriteMultipleToBinary(&testData, &vec);

			//blerg2.WriteToBinary(&testData);
			P2DE::FILEIO::FileIO::SaveBinaryFile(L"testData.bin", &testData);
			testData.clear();
		}

		if (P2DE_INPUT.IsKeyPressed(VK_KEY_5))
		{
			std::vector<P2DE::GFX::ImageProperties> vec;
			P2DE::FILEIO::FileIO::ReadBinaryFile(L"testData.bin", &testData);
			P2DE::GFX::ImageProperties::ReadMultipleFromBinary(&testData, vec);
			test1 = vec[0];
			test2 = vec[1];
			test3 = vec[2];
		}
		*/
		if (P2DE_INPUT.IsKeyPressed(VK_KEY_U))
		{
			if (P2DE_SFX.GetSound(L"pew")->GetPlaybackStatus() == P2DE::SFX::Status::Stopped)
				P2DE_SFX.GetSound(L"pew")->Play();
			else
				P2DE_SFX.GetSound(L"pew")->Stop();
		}
		
		if (P2DE_INPUT.IsKeyPressed(VK_KEY_I))
		{
			//if (music.getStatus() != P2DE::SFX::Status::Playing)
				//music.play();
			//else
				//music.stop();
		}

		P2DE_INPUT.ResetMousewheelState();

		return false;
	}
}
