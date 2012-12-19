#include "JoinGameState.h"

JoinGameState::JoinGameState()
{
	this->m_menu = new JoinGameMenu();
}

JoinGameState::~JoinGameState()
{
	delete this->m_menu;
}

void JoinGameState::update(float dt)
{
	this->m_menu->Update();
	
	if(this->m_menu->StartGameIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::GAME;
	}
	else if(this->m_menu->MainMenuGameIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::MAIN_MENU;
	}
}

State::StateEnum JoinGameState::nextState()
{
	return State::CREATE_GAME;
}