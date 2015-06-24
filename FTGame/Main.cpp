//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#include <Windows.h>
#include <DbgHelp.h>
#include <windowsx.h>

#include "Game\FTGame.h"
#include "P2DE\GFX\Graphics.h"
#include "P2DE\Timing\HrTimer.h"
#include "P2DE\Input\InputManager.h"

FTGame::FTGame* ftGame;
P2DE::GFX::Graphics* graphics;

#define WINDOW_TITLE L"Farm Time"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void make_minidump(EXCEPTION_POINTERS* e)
{
	auto hDbgHelp = LoadLibraryA("dbghelp");
	if (hDbgHelp == nullptr)
		return;
	auto pMiniDumpWriteDump = (decltype(&MiniDumpWriteDump))GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
	if (pMiniDumpWriteDump == nullptr)
		return;

	char name[MAX_PATH];
	{
		auto nameEnd = name + GetModuleFileNameA(GetModuleHandleA(0), name, MAX_PATH);
		SYSTEMTIME t;
		GetSystemTime(&t);
		wsprintfA(nameEnd - strlen(".exe"),
			"_%4d%02d%02d_%02d%02d%02d.dmp",
			t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
	}

	auto hFile = CreateFileA(name, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
	exceptionInfo.ThreadId = GetCurrentThreadId();
	exceptionInfo.ExceptionPointers = e;
	exceptionInfo.ClientPointers = FALSE;

	auto dumped = pMiniDumpWriteDump(
		GetCurrentProcess(),
		GetCurrentProcessId(),
		hFile,
		MINIDUMP_TYPE(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory),
		e ? &exceptionInfo : nullptr,
		nullptr,
		nullptr);

	CloseHandle(hFile);

	return;
}

LONG CALLBACK unhandled_handler(EXCEPTION_POINTERS* e)
{
	make_minidump(e);
	return EXCEPTION_CONTINUE_SEARCH;
}

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

	MSG msg = MSG();

	P2DE::TIMING::HrTimer hrTimer;

	while (TRUE && !ftGame->IsGameCrashed())
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

	P2DE::INPUT::InputManager::DeinitializeXboxControllers();

	delete ftGame;
	delete graphics;

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
			P2DE::INPUT::InputManager::SetMousewheelState(wParam);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}