#include "LobbyState.h"
#include "GameState.h"
#include "Input.h"

LobbyState::LobbyState()
{
	this->m_menu = new LobbyMenu();
}

LobbyState::~LobbyState()
{
	delete this->m_menu;
}

void LobbyState::update(float _dt)
{
	this->m_menu->Update();

	if(this->m_menu->StartGameIsDown() == true)
	{
		//Skicka ready till servern
	}

	//Kolla om nätverket har sagt att spelet har startat
}

State::StateEnum LobbyState::nextState()
{
	return State::GAME;
}