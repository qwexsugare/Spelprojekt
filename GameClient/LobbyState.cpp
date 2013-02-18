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
		m_network->sendMessage(NetworkSelectHeroMessage(0, this->m_menu->getCombat()));
	else if(m_menu->Character1IsDown())
		m_network->sendMessage(NetworkSelectHeroMessage(1, this->m_menu->getCombat()));
	else if(m_menu->Character2IsDown())
		m_network->sendMessage(NetworkSelectHeroMessage(2, this->m_menu->getCombat()));
	else if(m_menu->Character3IsDown())
		m_network->sendMessage(NetworkSelectHeroMessage(3, this->m_menu->getCombat()));
	else if(m_menu->Character4IsDown())
		m_network->sendMessage(NetworkSelectHeroMessage(4, this->m_menu->getCombat()));

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

	//Kolla om nätverket har sagt att spelet har startat
	while(!m_network->heroSelectedQueueEmpty())
	{
		NetworkHeroSelectedMessage nhsm = m_network->heroSelectedQueueFront();
		m_menu->selectHero(nhsm.getPlayerId(), Hero::HERO_TYPE(nhsm.getHeroId()));
	}
}

State::StateEnum LobbyState::nextState()
{
	return this->m_nextState;
}