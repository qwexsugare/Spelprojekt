#include "ClientHandler.h"

ClientHandler::ClientHandler()
{
	this->m_configFile = new ConfigFile();
	this->m_configFile->load();
}

ClientHandler::~ClientHandler()
{
	delete this->m_configFile;
	delete this->m_graphicsEngine;
	delete this->m_mouse;
}

INT2 ClientHandler::getScreenSize()const
{
	return INT2(this->m_configFile->getScreenSizeX(), this->m_configFile->getScreenSizeY());
}

void ClientHandler::initGraphicsEngine(HWND _hWnd)
{
	this->m_graphicsEngine = new GraphicsHandler(_hWnd, this->m_configFile);
	this->m_mouse = new Mouse(500, 500, _hWnd);

	Camera *c = this->m_graphicsEngine->getCamera();
}

HRESULT ClientHandler::run()
{
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
			this->m_graphicsEngine->render();
			
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
			/*case WM_KEYDOWN: // Key gets pressed
				this->m_keyboard.keyDown(this->m_messages[i].wParam);
				break;
					
			case WM_KEYUP: // Key gets released
				this->m_keyboard.keyUp(this->m_messages[i].wParam);
				break;
				*/
			case WM_LBUTTONDOWN: // Left mouse button down
				this->m_mouse->lButtonDown();
				break;

			case WM_RBUTTONDOWN: // Right mouse button down
				this->m_mouse->rButtonDown();
				break;

			case WM_LBUTTONUP: // Left mouse button up
				this->m_mouse->lButtonUp();
				break;

			case WM_RBUTTONUP: // Right mouse button up
				this->m_mouse->rButtonUp();
				break;
		}
	}
	this->m_messages.clear();
}