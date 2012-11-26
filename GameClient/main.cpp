#include <windows.h>
#include <iostream>
#include "GraphicsHandler.h"
#include "ConfigFile.h"
#include "Model.h"

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HWND	            InitWindow(HINSTANCE _hInstance, int _nCmdShow, const D3DXVECTOR2* _screenSize);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

GraphicsHandler *graphicsHandler;

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	ConfigFile configFile;
	configFile.load();

	HWND hwnd = 0;
	if((hwnd = InitWindow(hInstance, nCmdShow, configFile.getScreenSize())) == 0)
	{
		return 0;
	}

	graphicsHandler = new GraphicsHandler(hwnd, &configFile);
	Model *m = graphicsHandler->createModel("ArrowHead");
	Model *m = graphicsHandler->createModel("hero.obj");

	float r = 0.0f;
	m->setPosition(0.0f, 0.0f, 100.0f);

	// Main message loop
	MSG msg = {0};
	while(WM_QUIT != msg.message)
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			r = r + 0.001;
			m->setRotation(D3DXVECTOR3(r, r, 0.0f));
			graphicsHandler->render();
		}
	}

	delete graphicsHandler;

	return (int) msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HWND InitWindow(HINSTANCE _hInstance, int _nCmdShow, const D3DXVECTOR2* _screenSize)
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
	RECT rc = { 0, 0, 1024, 768 };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	hWnd = CreateWindow(	"Spelprojekt",
							"Spelprojekt",
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							_screenSize->x,
							_screenSize->y,
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