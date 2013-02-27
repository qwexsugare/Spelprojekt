#define WIN32_LEAN_AND_MEAN
#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <windows.h>
#include "ClientHandler.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "SoundWrapper.h"

ConfigFile* g_configFile;
GraphicsHandler* g_graphicsEngine;
Keyboard* g_keyboard;
Mouse* g_mouse;

HWND InitWindow(HINSTANCE _hInstance, int _nCmdShow, INT2 _screenSize);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPWSTR _lpCmdLine, int _nCmdShow)
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	srand((unsigned)time(0));

	// Load config into config file class
	g_configFile = new ConfigFile();
	g_configFile->load();

	// Init window
	HWND hwnd = 0;
	if((hwnd = InitWindow(_hInstance, _nCmdShow, g_configFile->getScreenSize())) == 0)
	{
		return 0;
	}
	
	initSoundEngine();
	
	setMusicVolume(g_configFile->getMusicVolume());
	setSoundVolume(g_configFile->getSoundVolume());
	
	ClientHandler* clientHandler = new ClientHandler(hwnd);
	HRESULT hr = clientHandler->run();
	delete clientHandler;
	
	deleteSoundEngine();

	return hr;
}

//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HWND InitWindow(HINSTANCE _hInstance, int _nCmdShow, INT2 _screenSize)
{
	HWND hWnd;

	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = _hInstance;
	wcex.hIcon          = 0;
	wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = "Spelprojekt";
	wcex.hIconSm        = 0;

	RegisterClassEx(&wcex);

	// Create window
	RECT rc = {0, 0, _screenSize.x, _screenSize.y};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindow(	"Spelprojekt",
							"Saints of The Asylum",
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							rc.right-rc.left,
							rc.bottom-rc.top,
							NULL,
							NULL,
							_hInstance,
							NULL);

	ShowWindow( hWnd, _nCmdShow );

	return hWnd;
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}