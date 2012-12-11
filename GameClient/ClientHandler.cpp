#include "ClientHandler.h"
#include "Input.h"
#include "Graphics.h"

ClientHandler::ClientHandler(HWND _hWnd, ConfigFile* _configFile)
{
	// Init globals for the people
	g_graphicsEngine = new GraphicsHandler(_hWnd, _configFile);
	g_mouse = new Mouse(500, 500, _hWnd);
	g_keyboard = new Keyboard();

	this->m_configFile = _configFile;
	g_graphicsEngine->getCamera()->set(FLOAT3(0.0f, 10.0f, 0.0f), FLOAT3(0.0f, -1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 1.0f), FLOAT3(1.0f, 0.0f, 0.0f));

	ServerThread *sh;
	//sh->Launch();
	//int i = 0;
}

ClientHandler::~ClientHandler()
{
	delete this->m_configFile;
	delete g_graphicsEngine;
	delete g_mouse;
	delete g_keyboard;
	delete this->m_state;
}

HRESULT ClientHandler::run()
{
	this->m_state = new GameState();

	__int64 cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	float secsPerCnt = 1.0f / (float)cntsPerSec;

	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);

	MSG msg = {0};
	while(WM_QUIT != msg.message)
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );

			this->m_messages.push_back(msg);
		}
		else
		{
			__int64 currTimeStamp = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
			float dt = (currTimeStamp - prevTimeStamp) * secsPerCnt;

			this->update(dt);
			g_graphicsEngine->update(dt);
			g_graphicsEngine->render();
			
			prevTimeStamp = currTimeStamp;
		}
	}

	return msg.wParam;
}

void ClientHandler::update(float _dt)
{
	// Update controls
	for(int i = 0; i < this->m_messages.size(); i++)
	{
		switch(this->m_messages[i].message)
		{
			case WM_KEYDOWN: // Key gets pressed
				g_keyboard->keyDown(this->m_messages[i].wParam);
				break;
			case WM_KEYUP: // Key gets released
				g_keyboard->keyUp(this->m_messages[i].wParam);
				break;
			case WM_LBUTTONDOWN: // Left mouse button down
				g_mouse->lButtonDown();
				break;
			case WM_RBUTTONDOWN: // Right mouse button down
				g_mouse->rButtonDown();
				break;
			case WM_LBUTTONUP: // Left mouse button up
				g_mouse->lButtonUp();
				break;
			case WM_RBUTTONUP: // Right mouse button up
				g_mouse->rButtonUp();
				break;
		}
	}
	this->m_messages.clear();
	
	this->m_state->update(_dt);

	static float CAMERA_SPEED = 2.0f;
	if((g_mouse->getPos().x >= this->m_configFile->getScreenSize().x-10 && g_mouse->getPos().x <= this->m_configFile->getScreenSize().x)
		|| g_keyboard->getKeyState(VK_RIGHT) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveRelative(0.0f, CAMERA_SPEED*_dt, 0.0f);
	}
	else if((g_mouse->getPos().x <= 10 && g_mouse->getPos().x >= 0)
		|| g_keyboard->getKeyState(VK_LEFT) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveRelative(0.0f, -(CAMERA_SPEED*_dt), 0.0f);
	}
	if((g_mouse->getPos().y >= this->m_configFile->getScreenSize().y-10 && g_mouse->getPos().y <= this->m_configFile->getScreenSize().y)
		|| g_keyboard->getKeyState(VK_DOWN) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveRelative(0.0f, 0.0f, CAMERA_SPEED*_dt);
	}
	else if((g_mouse->getPos().y <= 10 && g_mouse->getPos().y >= 0)
		|| g_keyboard->getKeyState(VK_UP) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveRelative(0.0f, 0.0f, -(CAMERA_SPEED*_dt));
	}

	g_mouse->update(); // Must be last!
}