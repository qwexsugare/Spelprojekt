#pragma once

#include "DataStructures.h"
#include "Mouse.h"
#include "Text.h"
#include "Camera.h"
#include "Keyboard.h"
#include "GameState.h"
#include "ServerThread.h"
#include <string>
using namespace std;

class ClientHandler
{
private:
	State* m_state;
	ConfigFile* m_configFile;
	vector<MSG> m_messages;
	Camera* m_camera;
public:
	ClientHandler(HWND _hWnd, ConfigFile* _configFile);
	~ClientHandler();
	
	HRESULT run();
	void update(float _dt);
};
