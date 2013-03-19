#pragma once

#include "GameState.h"
#include "MainMenuState.h"
#include "LobbyState.h"
#include "LoreState.h"
#include "CreateGameState.h"
#include "JoinGameState.h"
#include "ServerThread.h"
#include "CreditState.h"
#include "SettingsState.h"
#include "IntroState.h"
#include "client.h"
#include <string>
using namespace std;

class ClientHandler
{
private:
	State* m_state;
	Camera* m_camera;

	ServerThread *m_serverThread;
	Client *m_client;
public:
	ClientHandler(HWND _hWnd);
	~ClientHandler();

	HRESULT run();
	void update(float _dt);
};