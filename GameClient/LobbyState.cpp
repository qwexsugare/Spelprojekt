#include "LobbyState.h"
#include "GameState.h"
#include "Input.h"
#include "NetworkReadyMessage.h"

LobbyState::LobbyState()
{
	this->m_menu = new LobbyMenu();
}

LobbyState::LobbyState(Client* _network)
{
	this->m_network = _network;
	this->m_menu = new LobbyMenu();
}

LobbyState::~LobbyState()
{
	delete this->m_menu;
}

void LobbyState::update(float _dt)
{
	this->m_menu->Update(_dt);

	if(this->m_menu->StartGameIsDown() == true)
	{
		//Skicka ready till servern
		m_network->sendMessage(NetworkReadyMessage(true));
		this->setDone(true);
		this->m_nextState = State::GAME;
	}
	else if(this->m_menu->MainMenuIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::MAIN_MENU;
	}

	//Kolla om nätverket har sagt att spelet har startat
}

State::StateEnum LobbyState::nextState()
{
	return this->m_nextState;
}