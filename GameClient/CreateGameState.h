#ifndef CREATE_GAME_STATE
#define CREATE_GAME_STATE

#include "CreateGameMenu.h"
#include "State.h"
#include "Graphics.h"

class CreateGameState : public State
{
private:
	CreateGameMenu *m_menu;
	StateEnum m_nextState;
public:
	CreateGameState();
	~CreateGameState();

	void update(float dt);

	StateEnum nextState();
};

#endif