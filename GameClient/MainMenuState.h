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
	ParticleEngine* troll;
	ParticleEngine* troll1;
	ParticleEngine* troll2;
	ParticleEngine* troll3;
	D3DXVECTOR3 m_kewlPos;
public:
	MainMenuState();
	~MainMenuState();

	void update(float dt);
	StateEnum nextState();
};

#endif