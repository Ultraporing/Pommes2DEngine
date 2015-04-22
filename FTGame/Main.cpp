//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#include <Windows.h>
#include <windowsx.h>

#include "Game\FTGame.h"
#include "P2DE\GFX\Graphics.h"
#include "P2DE\Timing\HrTimer.h"

FTGame::FTGame* ftGame;
P2DE::GFX::Graphics* graphics;

#define WINDOW_TITLE L"Farm Time"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;           // Window Extended Style
	DWORD dwStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);  // Windows Style

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	RegisterClassEx(&wc);

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, dwStyle, false, dwExStyle);

	hWnd = CreateWindowEx(
		dwExStyle,
		L"WindowClass1",
		WINDOW_TITLE,
		dwStyle,
		300,
		300,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	graphics = NULL;
	graphics = new P2DE::GFX::Graphics();
	if (!graphics->Init(hWnd, dwStyle, dwExStyle))
	{
		delete graphics;
		return -1;
	}

	ftGame = NULL;
	ftGame = new FTGame::FTGame(graphics, hWnd);

	ShowWindow(hWnd, nCmdShow);

	MSG msg;

	P2DE::TIMING::HrTimer hrTimer;

	while (TRUE)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		if (msg.message == WM_QUIT)
			break;

		hrTimer.Update();

		if (ftGame->Update(hrTimer.GetDeltaTime())) // Shutdown game if TRUE is returned
			PostQuitMessage(0);

		ftGame->Render();
	}

	delete ftGame;
	delete graphics;

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}