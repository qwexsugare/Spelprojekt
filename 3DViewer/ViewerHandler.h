#pragma once

#include "Mouse.h"
#include "Camera.h"
#include "Keyboard.h"
#include <string>
#include "GraphicsHandler.h"

#include <Windows.h>

#include "Input.h"
#include "Graphics.h"

using namespace std;

class ViewerHandler
{
private:
	ConfigFile* m_configFile;
	vector<MSG> m_messages;
	Camera* m_camera;
	int m_modelCount; 
	Model *m_shownModel;
	float m_yaw, m_pitch, m_roll;

public:
	ViewerHandler(HWND _hWnd, ConfigFile* _configFile);
	~ViewerHandler();
	
	HWND *m_wnd;
	HRESULT run();
	void update(float _dt);
	std::string test; 
	void ReadFile(HWND hw);


};
