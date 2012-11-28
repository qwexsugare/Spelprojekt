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

	Model* m_testModel;
	Text* m_fpsText;
public:
	ClientHandler();
	~ClientHandler();

	INT2 getScreenSize()const;
	void initGraphicsEngine(HWND _hWnd);
	HRESULT run();
	void update(float _dt);
};
