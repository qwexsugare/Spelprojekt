#pragma once
#include "state.h"
#include "IntroMenu.h"
class IntroState :
	public State
{
private:
	IntroMenu *m_menu;
	StateEnum m_nextState;
public:
	IntroState();
	~IntroState();

	void update(float dt);

	StateEnum nextState();
	float time;
};

