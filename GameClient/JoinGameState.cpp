#include "JoinGameState.h"

JoinGameState::JoinGameState(Client *_network) : State(State::JOIN_GAME)
{
	this->m_menu = new JoinGameMenu();
	this->m_network = _network;
	this->m_connectingText = g_graphicsEngine->createText("", INT2(g_graphicsEngine->getScreenSize().x / 2 - 200, g_graphicsEngine->getScreenSize().y / 2), 40, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

JoinGameState::~JoinGameState()
{
	delete this->m_menu;
	g_graphicsEngine->removeText(this->m_connectingText);
}

void JoinGameState::update(float dt)
{
	this->m_menu->Update(dt);
	
	if(this->m_menu->StartGameIsDown() == true)
	{
		//Try to connect to the server
		this->m_connectingText->setString("Connecting to server...");
		g_graphicsEngine->render();

		if(this->m_network->connect(this->getIP(), this->getPort()) == true)
		{
			m_menu->savePlayerName();
			this->setDone(true);
			this->m_nextState = State::LOBBY;
		}
		else
		{
			this->m_connectingText->setString("Could not connect to server");
		}
	}
	else if(this->m_menu->MainMenuGameIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::MAIN_MENU;
	}
}

State::StateEnum JoinGameState::nextState()
{
	return this->m_nextState;
}

string JoinGameState::getIP()
{
	return this->m_menu->getIP();
}

int JoinGameState::getPort()
{
	return atoi(this->m_menu->getPort().c_str());
}

string JoinGameState::getPlayerName()
{
	return this->m_menu->getPlayerName();
}