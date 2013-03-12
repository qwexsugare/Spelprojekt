#pragma once

#include "state.h"
#include "Graphics.h"
#include "NetworkEndGameMessage.h"

class EndState : public State
{
private:
	Sprite *m_background;
public:
	EndState(NetworkEndGameMessage endMessage);
	~EndState();

	StateEnum nextState();
	void update(float _dt);
};

