//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#include <Windows.h>

#include "Game\Demo.h"
#include "P2DE\GFX\Graphics.h"
#include "P2DE\Timing\HrTimer.h"
#include "P2DE\Input\InputManager.h"
#include "P2DE\Utilities\Minidump.h"


#define WINDOW_TITLE L"Engine Demo"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetUnhandledExceptionFilter(unhandled_handler);

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
	
	if (!P2DE_GFX.Init(hWnd, dwStyle, dwExStyle))
	{
		return -1;
	}

	Demo::Demo demo = Demo::Demo(hWnd);

	ShowWindow(hWnd, nCmdShow);

	MSG msg = MSG();

	P2DE::TIMING::HrTimer hrTimer;

	while (TRUE && !demo.IsGameCrashed())
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		if (msg.message == WM_QUIT)
			break;

		hrTimer.Update();

		if (demo.Update(hrTimer.GetDeltaTime())) // Shutdown game if TRUE is returned
			PostQuitMessage(0);

		//TODO: SOMEWHERE IN ENGINE RENDERING IS AN MEMORY LEAK!
		demo.Render();
	}



	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_MOUSEWHEEL:
			P2DE_INPUT.SetMousewheelState(wParam);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}