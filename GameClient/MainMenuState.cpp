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
	float speed = 2.5f;
	m_kewlPos.z = 4;
	if(GetKeyState(VK_LEFT) < 0)
	{
		if(m_kewlPos.x >= -1)
		{			
			m_kewlPos.x += -speed*dt;
		}
	}
	if(GetKeyState(VK_RIGHT) < 0)
	{
		if(m_kewlPos.x <= 1)
		{
			m_kewlPos.x += speed*dt;
		}
	}

	if(GetKeyState(VK_DOWN) < 0)
	{
		if(m_kewlPos.y >= -1)
		{			
			m_kewlPos.y += -speed*dt;
		}
	}
	if(GetKeyState(VK_UP) < 0)
	{
		if(m_kewlPos.y <= 1)
		{
			m_kewlPos.y += speed*dt;
		}
	}

	//troll->setPosition(m_kewlPos);
	//troll1->setPosition(m_kewlPos);
	//troll2->setPosition(m_kewlPos);



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