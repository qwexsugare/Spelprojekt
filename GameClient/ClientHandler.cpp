#include "ClientHandler.h"
#include "Input.h"
#include "Graphics.h"
#include "SoundWrapper.h"
#include "EndState.h"
#include "LoadingState.h"

ClientHandler::ClientHandler(HWND _hWnd)
{
	// Init globals for the people
	g_graphicsEngine = new GraphicsHandler(_hWnd, g_configFile);
	g_mouse = new Mouse(500, 500, _hWnd);
	g_keyboard = new Keyboard();

	this->m_serverThread = NULL;
	this->m_client = new Client();
}

ClientHandler::~ClientHandler()
{
	if(this->m_serverThread)
	{
		delete this->m_serverThread;
	}
	if(this->m_state)
	{
		delete this->m_state;
	}
	if(this->m_client)
	{
		this->m_client->disconnect();
		delete this->m_client;
	}
	delete g_graphicsEngine;
	delete g_mouse;
	delete g_keyboard;
	delete g_configFile;
}

HRESULT ClientHandler::run()
{
	//this->m_serverThread->Launch();
	this->m_state = new MainMenuState();

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

void ClientHandler::update(float _dt)
{
	this->m_state->update(_dt);
	if(this->m_state->isDone())
	{
		State* tempState = this->m_state;

		switch(this->m_state->nextState())
		{
		case State::INTRO:
			this->m_state = new IntroState();
			break;
		case State::MAIN_MENU:
			if(tempState->getType() == State::LOBBY)
			{
				ClientEntityHandler::removeAllEntities();
				this->m_client->disconnect();
				delete this->m_serverThread;
				this->m_serverThread = NULL;
			}

			this->m_state = new MainMenuState();
			break;
		case State::CREATE_GAME:
			this->m_state = new CreateGameState();
			break;
		case State::JOIN_GAME:
			this->m_state = new JoinGameState(this->m_client);
			break;
		case State::LOBBY:
			if(tempState->getType() == State::CREATE_GAME)
			{
				CreateGameState *tempCreateState = (CreateGameState*)tempState;

				this->m_serverThread = new ServerThread(tempCreateState->getPort(), tempCreateState->getMapName());
				this->m_serverThread->Launch();

				this->m_client->connect(tempCreateState->getIP(), tempCreateState->getPort());

				//sends le player name, code 1337, hardcoded
				sf::Packet playerName;
				playerName << (int)NetworkMessage::setPlayerName << tempCreateState->getPlayerName();
				this->m_client->sendPacket(playerName);
			}
			else
			{
				JoinGameState *tempJoinState = (JoinGameState*)tempState;
				//sends le player name, code 1337, hardcoreporn
				sf::Packet playerName;
				playerName << (int)NetworkMessage::setPlayerName << tempJoinState->getPlayerName();
				this->m_client->sendPacket(playerName);
			}

			this->m_state = new LobbyState(this->m_client);
			break;
		case State::LORE:
			this->m_state = new LoreState();
			break;
		case State::GAME:
			if(tempState->getType() == State::LOADING)
			{
				LoadingState *tempLoadingState = (LoadingState*)tempState;
				this->m_state = new GameState(this->m_client, tempLoadingState->getMapName());
			}
			else
			{
				this->m_state = new GameState(this->m_client, "levelone");
			}
			break;
		case State::SETTINGS:
			this->m_state = new SettingsState();
			break;
		case State::CREDITS:
			this->m_state = new CreditState();
			break;
		case State::END:
			ClientEntityHandler::removeAllEntities();
			this->m_client->disconnect();
			delete this->m_serverThread;
			this->m_serverThread = NULL;
			this->m_state = new EndState(((GameState*)tempState)->getEndGameMessage());
			break;
		case State::LOADING:
			{
				LobbyState *tempLobbyState = (LobbyState*)tempState;
				string temp = tempLobbyState->getMapName();
				delete tempState;
				tempState = NULL;
				this->m_state = new LoadingState(m_client, temp);
			}
			break;
		case State::EXIT:
			this->m_state = NULL;
			PostQuitMessage(0);
			break;
		}

		delete tempState;
	}

	D3DXVECTOR3 camPos = g_graphicsEngine->getCamera()->getPos();
	updateSoundEngine(FLOAT3(camPos.x, camPos.y, camPos.z));

	g_mouse->update(); // Must be last! WHY?! - Because otherwise the mouse buttons will NEVER be "pressed"
	g_keyboard->update();
}