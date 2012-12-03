#pragma once

#include "GraphicsHandler.h"
#include "DataStructures.h"
#include "Mouse.h"
#include "Text.h"
#include "Camera.h"
#include "Keyboard.h"
#include <string>
using namespace std;

class ClientHandler
{
private:
	Keyboard* m_keyboard;
	Mouse* m_mouse;
	ConfigFile* m_configFile;
	GraphicsHandler* m_graphicsEngine;
	vector<MSG> m_messages;
	Camera* m_camera;
	
	// Developing/test stuff
	Model* m_testModel;
	Text* m_fpsText;
public:
	ClientHandler(HWND _hWnd, ConfigFile* _configFile);
	~ClientHandler();
	
	HRESULT run();
	void update(float _dt);
};
