#pragma once
#include "State.h"
#include "JoinGameMenu.h"
#include "client.h"

class JoinGameState : public State
{
private:
	JoinGameMenu *m_menu;
	StateEnum m_nextState;
	bool waitingForServerToStart;
	Client *m_network;
	Text* m_connectingText;
public:
	JoinGameState(Client *_network);
	~JoinGameState();

	void update(float dt);
	StateEnum nextState();

	string getIP();
	int getPort();
	string getPlayerName();
};

