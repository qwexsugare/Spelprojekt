#include "LobbyState.h"
#include "GameState.h"
#include "Input.h"
#include "NetworkReadyMessage.h"

LobbyState::LobbyState()
{

}

LobbyState::LobbyState(Client* _network)
{
	this->m_network = _network;
	this->m_menu = new LobbyMenu();
	m_lastRcvdHeroSelectedId = -1;
}

LobbyState::~LobbyState()
{
	delete this->m_menu;
}

void LobbyState::update(float _dt)
{
	this->m_menu->Update(_dt);

	if(m_menu->Character0IsDown())
		m_network->sendMessage(NetworkSelectHeroMessage(0));
	else if(m_menu->Character1IsDown())
		m_network->sendMessage(NetworkSelectHeroMessage(1));
	else if(m_menu->Character2IsDown())
		m_network->sendMessage(NetworkSelectHeroMessage(2));
	else if(m_menu->Character3IsDown())
		m_network->sendMessage(NetworkSelectHeroMessage(3));
	else if(m_menu->Character4IsDown())
		m_network->sendMessage(NetworkSelectHeroMessage(4));

	if(this->m_menu->StartGameIsDown() == true)
	{
		//Skicka ready till servern
		m_network->sendMessage(NetworkReadyMessage(true));
	}
	else if(this->m_menu->MainMenuIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::MAIN_MENU;
	}

	//Kolla om nätverket har sagt att spelet har startat
	while(!m_network->startGameQueueEmpty())
	{
		m_network->startGameQueueFront();
		this->setDone(true);
		this->m_nextState = State::GAME;
	}
}

State::StateEnum LobbyState::nextState()
{
	return this->m_nextState;
}