#pragma once

#include "GraphicsHandler.h"
#include "DataStructures.h"
#include "Mouse.h"
#include "Text.h"
#include <string>
using namespace std;

class ClientHandler
{
private:
	Mouse* m_mouse;
	ConfigFile* m_configFile;
	GraphicsHandler* m_graphicsEngine;
	vector<MSG> m_messages;
	
	// Developing/test stuff
	Model* m_testModel;
	Text* m_fpsText;

public:
	ClientHandler(HWND _hWnd, ConfigFile* _configFile);
	~ClientHandler();
	
	void initGame();
	HRESULT run();
	void update(float _dt);
};
