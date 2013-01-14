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
		this->m_nextState = State::GAME;
	}
}

State::StateEnum MainMenuState::nextState()
{
	return this->m_nextState;
}