#include "ClientHandler.h"
#include <sstream>

ClientHandler::ClientHandler(HWND _hWnd, ConfigFile* _configFile)
{
	this->m_configFile = _configFile;
	this->m_graphicsEngine = new GraphicsHandler(_hWnd, this->m_configFile);
	this->m_mouse = new Mouse(500, 500, _hWnd);
	this->m_keyboard = new Keyboard();
	
	this->m_graphicsEngine->getCamera()->set(FLOAT3(0.0f, 10.0f, 0.0f), FLOAT3(0.0f, -1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 1.0f), FLOAT3(1.0f, 0.0f, 0.0f));
	this->m_testModel = NULL;
	this->m_fpsText = this->m_graphicsEngine->createText("10", INT2(50, 100), 100, D3DXCOLOR(0.5f, 0.2f, 0.8f, 1.0f));
}

ClientHandler::~ClientHandler()
{
	delete this->m_configFile;
	delete this->m_graphicsEngine;
	delete this->m_mouse;
	delete this->m_keyboard;
}

HRESULT ClientHandler::run()
{
	Model *m1 = this->m_graphicsEngine->createModel("ArrowHead");
	m1->setPosition(0.0f, 3.0f, 0.0f);
	m1->setAlpha(0.5f);

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
	// Update FRAMES PER SECOND (FPS) text
	static float lol = 0.0f;
	lol += _dt;
	if(lol > 0.0f)
	{
		lol = -0.5f;
		stringstream ss;
		ss << "FPS: " << 1.0f/_dt;
		this->m_fpsText->setString(ss.str());
	}

	// Update controls
	for(int i = 0; i < this->m_messages.size(); i++)
	{
		switch(this->m_messages[i].message)
		{
			case WM_KEYDOWN: // Key gets pressed
				this->m_keyboard->keyDown(this->m_messages[i].wParam);
				break;
			case WM_KEYUP: // Key gets released
				this->m_keyboard->keyUp(this->m_messages[i].wParam);
				break;
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
	

	if(this->m_mouse->isLButtonPressed())
	{
		this->m_testModel = this->m_graphicsEngine->createModel("ArrowHead");
		//this->m_testModel->setPosition(this->m_graphicsEngine->getCameraPos().x, 0.0f, this->m_graphicsEngine->getCameraPos().z);
	}
	if(this->m_mouse->isRButtonDown())
	{
		if(this->m_testModel)
			this->m_testModel->rotate(0.0025f, 0.0f, 0.0f);
	}
	
	static float CAMERA_SPEED = 2.0f;
	if((this->m_mouse->getPos().x >= this->m_configFile->getScreenSize().x-10 && this->m_mouse->getPos().x <= this->m_configFile->getScreenSize().x)
		|| this->m_keyboard->getKeyState(VK_RIGHT) != Keyboard::KEY_UP)
	{
		this->m_graphicsEngine->getCamera()->moveRelative(0.0f, CAMERA_SPEED*_dt, 0.0f);
	}
	else if((this->m_mouse->getPos().x <= 10 && this->m_mouse->getPos().x >= 0)
		|| this->m_keyboard->getKeyState(VK_LEFT) != Keyboard::KEY_UP)
	{
		this->m_graphicsEngine->getCamera()->moveRelative(0.0f, -(CAMERA_SPEED*_dt), 0.0f);
	}
	if((this->m_mouse->getPos().y >= this->m_configFile->getScreenSize().y-10 && this->m_mouse->getPos().y <= this->m_configFile->getScreenSize().y)
		|| this->m_keyboard->getKeyState(VK_DOWN) != Keyboard::KEY_UP)
	{
		this->m_graphicsEngine->getCamera()->moveRelative(0.0f, 0.0f, CAMERA_SPEED*_dt);
	}
	else if((this->m_mouse->getPos().y <= 10 && this->m_mouse->getPos().y >= 0)
		|| this->m_keyboard->getKeyState(VK_UP) != Keyboard::KEY_UP)
	{
		this->m_graphicsEngine->getCamera()->moveRelative(0.0f, 0.0f, -(CAMERA_SPEED*_dt));
	}

	this->m_mouse->update(); // Must be last!
}