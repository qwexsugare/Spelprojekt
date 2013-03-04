#pragma once
#include "state.h"
#include "SettingsMenu.h"

class SettingsState :
	public State
{
private:
	SettingsMenu *m_menu;
	StateEnum m_nextState;
public:
	SettingsState();
	~SettingsState();

	void update(float dt);

	StateEnum nextState();
};

