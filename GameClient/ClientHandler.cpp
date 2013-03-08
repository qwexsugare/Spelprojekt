#include "ClientHandler.h"
#include "Input.h"
#include "Graphics.h"
#include "SoundWrapper.h"

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

	// Retarded thread code
	/*this->update(0.0f);
	g_graphicsEngine->Launch();*/

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

void ClientHandler::update(float _dt)
{
	// Update controls
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
			this->m_state = new MainMenuState();
			break;
		case State::CREATE_GAME:
			this->m_state = new CreateGameState();
			break;
		case State::JOIN_GAME:
			this->m_state = new JoinGameState();
			break;
		case State::LOBBY:
			if(tempState->getType() == State::CREATE_GAME)
			{
				CreateGameState *tempCreateState = (CreateGameState*)tempState;

				this->m_serverThread = new ServerThread(tempCreateState->getPort());
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
				this->m_client->connect(tempJoinState->getIP(), tempJoinState->getPort());

				//sends le player name, code 1337, hardcoded
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
			if(tempState->getType() == State::LOBBY)
			{
				LobbyState *tempLobbyState = (LobbyState*)tempState;
				this->m_state = new GameState(this->m_client, tempLobbyState->getMapName());
			}
			else
			{
				this->m_state = new GameState(this->m_client, "levelone.txt");
			}
			break;
		case State::SETTINGS:
			this->m_state = new SettingsState();
			break;
		case State::CREDITS:
			this->m_state = new CreditState();
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

	g_mouse->update(); // Must be last! WHY?!
	g_keyboard->update();
}