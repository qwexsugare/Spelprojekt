#pragma once

#include "State.h"

class LobbyState : public State
{
public:
	LobbyState();
	~LobbyState();

	void update(float _dt);
	bool done();
	State* nextState();
};