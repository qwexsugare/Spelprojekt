#include "IntroState.h"
#include "Input.h"
IntroState::IntroState(void)
{
	this->m_menu = new IntroMenu();
	time = 0;
}

IntroState::~IntroState()
{
	delete this->m_menu;
}

void IntroState::update(float dt)
{
	this->m_menu->Update(dt);
	time += dt;
	if(g_keyboard->getKeyState(VK_SPACE) == g_keyboard->KEY_PRESSED || this->m_menu->m_counter < time && this->m_menu->forthRun == true)
	{
		this->setDone(true);
		this->m_nextState = State::MAIN_MENU;
	}
}

State::StateEnum IntroState::nextState()
{
	return this->m_nextState;
}
