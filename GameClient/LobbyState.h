#pragma once

#include "State.h"
#include "LobbyMenu.h"

class LobbyState : public State
{
private:
	LobbyMenu *m_menu;
	StateEnum  m_nextState;
public:
	LobbyState();
	~LobbyState();

	void update(float _dt);
	StateEnum nextState();
};