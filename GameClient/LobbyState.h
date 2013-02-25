#pragma once

#include "State.h"
#include "LobbyMenu.h"
#include "client.h"

class LobbyState : public State
{
private:
	LobbyMenu *m_menu;
	StateEnum  m_nextState;
	Client* m_network;
	int m_currentHeroSelected;
	Hero::HERO_TYPE m_heroType;
public:
	LobbyState();
	LobbyState(Client* _network);
	~LobbyState();

	void update(float _dt);
	StateEnum nextState();
};