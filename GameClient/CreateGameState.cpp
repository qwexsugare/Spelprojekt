#include "CreateGameState.h"

CreateGameState::CreateGameState()
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