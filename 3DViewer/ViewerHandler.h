#pragma once

#include "Mouse.h"
#include "Camera.h"
#include "Keyboard.h"
#include <string>
#include "GraphicsHandler.h"
using namespace std;

class ViewerHandler
{
private:
	ConfigFile* m_configFile;
	vector<MSG> m_messages;
	Camera* m_camera;
public:
	ViewerHandler(HWND _hWnd, ConfigFile* _configFile);
	~ViewerHandler();
	
	HRESULT run();
	void update(float _dt);
};
