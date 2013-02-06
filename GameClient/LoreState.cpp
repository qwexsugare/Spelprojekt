#include "LoreState.h"
#include "GameState.h"
#include "Input.h"

LoreState::LoreState()
{
	this->m_menu = new LoreMenu();
}

LoreState::~LoreState()
{
	delete this->m_menu;
}

void LoreState::update(float _dt)
{
	this->m_menu->Update();

	if(this->m_menu->MainMenuIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::MAIN_MENU;
	}
}

State::StateEnum LoreState::nextState()
{
	return this->m_nextState;
}
