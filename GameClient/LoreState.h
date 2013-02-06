#pragma once

#include "State.h"
#include "LoreMenu.h"

class LoreState : public State
{
private:
	LoreMenu *m_menu;
	StateEnum m_nextState;
public:
	LoreState();
	~LoreState();

	void update(float _dt);
	StateEnum nextState();
};

