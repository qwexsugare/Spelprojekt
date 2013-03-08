#include "LobbyState.h"
#include "GameState.h"
#include "Input.h"
#include "NetworkReadyMessage.h"

LobbyState::LobbyState() : State(State::LOBBY)
{

}

LobbyState::LobbyState(Client* _network) : State(State::LOBBY)
{
	this->m_network = _network;
	this->m_menu = new LobbyMenu();
	m_currentHeroSelected = Hero::HERO_TYPE::NONE;
}

LobbyState::~LobbyState()
{
	delete this->m_menu;
}

void LobbyState::update(float _dt)
{
	this->m_menu->Update(_dt);

	if(m_menu->Character0IsDown())
	{
		this->m_currentHeroSelected = Hero::OFFICER;
		m_network->sendMessage(NetworkSelectHeroMessage(0, this->m_menu->getCombat()));
	}
	else if(m_menu->Character1IsDown())
	{
		this->m_currentHeroSelected = Hero::RED_KNIGHT;
		m_network->sendMessage(NetworkSelectHeroMessage(1, this->m_menu->getCombat()));
	}
	else if(m_menu->Character2IsDown())
	{
		this->m_currentHeroSelected = Hero::ENGINEER;
		m_network->sendMessage(NetworkSelectHeroMessage(2, this->m_menu->getCombat()));
	}
	else if(m_menu->Character3IsDown())
	{
		this->m_currentHeroSelected = Hero::DOCTOR;
		m_network->sendMessage(NetworkSelectHeroMessage(3, this->m_menu->getCombat()));
	}
	else if(m_menu->Character4IsDown())
	{
		this->m_currentHeroSelected = Hero::THE_MENTALIST;
		m_network->sendMessage(NetworkSelectHeroMessage(4, this->m_menu->getCombat()));
	}
	else if(m_menu->MainMenuIsDown())
	{
		this->m_network->disconnect();
	}

	if(this->m_menu->CloseCombatIsDown() && this->m_currentHeroSelected != Hero::NONE)
	{
		this->m_network->sendMessage(NetworkSelectHeroMessage(this->m_currentHeroSelected, this->m_menu->getCombat()));
	}
	else if(this->m_menu->RangeCombatIsDown() && this->m_currentHeroSelected != Hero::NONE)
	{
		this->m_network->sendMessage(NetworkSelectHeroMessage(this->m_currentHeroSelected, this->m_menu->getCombat()));
	}

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
		NetworkStartGameMessage e = m_network->startGameQueueFront();
		this->mapName = e.getMapName();
		this->setDone(true);
		this->m_nextState = State::GAME;
	}

	while(!m_network->heroSelectedQueueEmpty())
	{
		NetworkHeroSelectedMessage nhsm = m_network->heroSelectedQueueFront();
		m_heroType = Hero::HERO_TYPE(nhsm.getHeroId());
		m_menu->selectHero(nhsm.getPlayerId(), m_heroType);
	}

	while(!m_network->networkWelcomeMessageEmpty())
	{
		NetworkWelcomeMessage nwm = m_network->networkWelcomeMessageFront();
		this->mapName = nwm.getMapName();
	}
}

State::StateEnum LobbyState::nextState()
{
	return this->m_nextState;
}
string LobbyState::getMapName()
{
	return this->mapName;
}