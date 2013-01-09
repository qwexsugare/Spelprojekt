#include "ViewerHandler.h"
#include "commdlg.h"

using namespace std;

ViewerHandler::ViewerHandler(HWND _hWnd, ConfigFile* _configFile)
{
	
	// Init globals for the people
	g_graphicsEngine = new GraphicsHandler(_hWnd, _configFile);
	g_mouse = new Mouse(500, 500, _hWnd);
	g_keyboard = new Keyboard();
	
	m_yaw = 0.0f;
	m_pitch = 0.0f;
	m_roll = 0.0f;
	//ReadFile(_hWnd);
	
	this->m_configFile = _configFile;
	g_graphicsEngine->getCamera()->set(FLOAT3(0.0f, 10.0f, 0.0f), FLOAT3(0.0f, -1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 1.0f), FLOAT3(1.0f, 0.0f, 0.0f));
}

ViewerHandler::~ViewerHandler()
{
	delete this->m_configFile;
	delete g_graphicsEngine;
	delete g_mouse;
	delete g_keyboard;
}

HRESULT ViewerHandler::run()
{
	

	m_shownModel = g_graphicsEngine->createModel("ArrowHead", FLOAT3(.0f, 0.0f, 0.0f), false);
	
	
	//delete model;


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

void ViewerHandler::update(float _dt)
{
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

	static float CAMERA_SPEED = 2.0f;
	if((g_mouse->getPos().x >= this->m_configFile->getScreenSize().x-10 && g_mouse->getPos().x <= this->m_configFile->getScreenSize().x)
		|| g_keyboard->getKeyState(VK_RIGHT) != Keyboard::KEY_UP)
	{
		m_roll -= 0.001f;
	}
	else if((g_mouse->getPos().x <= 10 && g_mouse->getPos().x >= 0)
		|| g_keyboard->getKeyState(VK_LEFT) != Keyboard::KEY_UP)
	{
		m_roll += 0.001f;
	}
	if(g_keyboard->getKeyState(VK_NUMPAD1) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->removeModel(m_shownModel);
		m_shownModel = g_graphicsEngine->createModel("cylinder", FLOAT3(.0f, 0.0f, 0.0f), false);
	}
	if(g_keyboard->getKeyState(VK_NUMPAD2) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->removeModel(m_shownModel);
		m_shownModel = g_graphicsEngine->createModel("ArrowHead", FLOAT3(.0f, 0.0f, 0.0f), false);
	}

	if(m_roll < 0)
		m_roll = 2*3.141591;
	if(m_roll > 2*3.141592)
		m_roll = 0; 

	m_shownModel->setRotation(m_yaw, m_pitch, m_roll);

	g_mouse->update(); // Must be last!
}

void ViewerHandler::ReadFile(HWND hw)
{
	
	char fp[MAX_PATH] = "";
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hw;//GetDesktopWindow();
	ofn.lpstrFilter = "Fish Files(*.obj)\0*.obj\0All Files(*.*)\0*.*\0";
	ofn.lpstrFile = fp;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "fish";
	
	
	if(GetOpenFileName(&ofn))
	{
		test = fp;
		OutputDebugStringA(test.c_str());
	}
	

	

	

	
}