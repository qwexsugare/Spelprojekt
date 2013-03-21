#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
	this->m_menu = new MainMenu();
	troll = NULL; //g_graphicsEngine->createParticleEngine("blood", D3DXVECTOR4(0, 0, 4, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));
	troll1 = NULL;//g_graphicsEngine->createParticleEngine("test2", D3DXVECTOR4(0, 0, 4, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));
	troll2 = NULL;//g_graphicsEngine->createParticleEngine("test3", D3DXVECTOR4(0, 0, 4, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));
	troll3 = NULL; //g_graphicsEngine->createParticleEngine("DeamonSpit", D3DXVECTOR4(0, 1, 4, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));
}

MainMenuState::~MainMenuState()
{
	delete this->m_menu;
	g_graphicsEngine->removeParticleEngine(troll);
	g_graphicsEngine->removeParticleEngine(troll1);
	g_graphicsEngine->removeParticleEngine(troll2);
	g_graphicsEngine->removeParticleEngine(troll3);
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