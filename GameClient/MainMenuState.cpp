#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
	this->m_menu = new MainMenu();
}

MainMenuState::~MainMenuState()
{
	delete this->m_menu;
}

void MainMenuState::update(float dt)
{
	this->m_menu->Update();

	if(this->m_menu->createGameIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::CREATE_GAME;
	}
	if(this->m_menu->JoinGameIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::JOIN_GAME;
	}
	if(this->m_menu->SettingsIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::SETTINGS;
	}
	if(this->m_menu->LoreIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::LORE;
	}
	if(this->m_menu->CreditsIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::CREDITS;
	}
	if(this->m_menu->ExitIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::EXIT;
	}
}

State::StateEnum MainMenuState::nextState()
{
	return this->m_nextState;
}