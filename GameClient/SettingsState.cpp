#include "SettingsState.h"


SettingsState::SettingsState(void)
{
	this->m_menu = new SettingsMenu();
}

SettingsState::~SettingsState()
{
	delete this->m_menu;
}

void SettingsState::update(float dt)
{
	this->m_menu->Update();

	 if(this->m_menu->MainMenuIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::MAIN_MENU;
	}
}

State::StateEnum SettingsState::nextState()
{
	return this->m_nextState;
}

