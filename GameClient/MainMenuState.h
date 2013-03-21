#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "Graphics.h"
#include "State.h"
#include "MainMenu.h"

class MainMenuState : public State
{
private:
	MainMenu *m_menu;
	StateEnum m_nextState;
	D3DXVECTOR3 m_kewlPos;
public:
	MainMenuState();
	~MainMenuState();

	void update(float dt);
	StateEnum nextState();
};

#endif