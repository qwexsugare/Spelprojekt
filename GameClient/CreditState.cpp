#include "CreditState.h"


CreditState::CreditState(void)
{
	this->m_menu = new CreditsMenu();
}

CreditState::~CreditState()
{
	delete this->m_menu;
}

void CreditState::update(float dt)
{
	this->m_menu->Update();

	 if(this->m_menu->MainMenuGameIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::MAIN_MENU;
	}
}

State::StateEnum CreditState::nextState()
{
	return this->m_nextState;
}
