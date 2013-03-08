#pragma once
#include "State.h"
#include "JoinGameMenu.h"

class JoinGameState : public State
{
private:
	JoinGameMenu *m_menu;
	StateEnum m_nextState;
	bool waitingForServerToStart;
public:
	JoinGameState();
	~JoinGameState();

	void update(float dt);
	StateEnum nextState();

	string getIP();
	int getPort();
	string getPlayerName();
};

