#pragma once
#include "CreditsMenu.h"
#include "State.h"
#include "Graphics.h"

class CreditState : public State
{
private:
	CreditsMenu *m_menu;
	StateEnum m_nextState;
public:
	CreditState();
	~CreditState();

	void update(float dt);

	StateEnum nextState();
};

