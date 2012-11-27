#pragma once

#include "GraphicsHandler.h"
#include "DataStructures.h"
#include "Mouse.h"

class ClientHandler
{
private:
	Mouse* m_mouse;
	ConfigFile* m_configFile;
	GraphicsHandler* m_graphicsEngine;
	vector<MSG> m_messages;
public:
	ClientHandler();
	~ClientHandler();

	INT2 getScreenSize()const;
	void initGraphicsEngine(HWND _hWnd);
	HRESULT run();
	void update(float _dt);
};
