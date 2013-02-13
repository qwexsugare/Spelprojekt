#include "JoinGameState.h"

JoinGameState::JoinGameState() : State(State::JOIN_GAME)
{
	this->m_menu = new JoinGameMenu();
}

JoinGameState::~JoinGameState()
{
	delete this->m_menu;
}

void JoinGameState::update(float dt)
{
	this->m_menu->Update(dt);
	
	if(this->m_menu->StartGameIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::LOBBY;
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