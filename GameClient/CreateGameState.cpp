#include "CreateGameState.h"

CreateGameState::CreateGameState() : State(State::CREATE_GAME)
{
	this->m_menu = new CreateGameMenu();
}

CreateGameState::~CreateGameState()
{
	delete this->m_menu;
}

void CreateGameState::update(float dt)
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

State::StateEnum CreateGameState::nextState()
{
	return this->m_nextState;
}

string CreateGameState::getIP()
{
	return this->m_menu->getIP();
}

int CreateGameState::getPort()
{
	return atoi(this->m_menu->getPort().c_str());
}

string CreateGameState::getPlayerName()
{
	return this->m_menu->getPlayerName();
}