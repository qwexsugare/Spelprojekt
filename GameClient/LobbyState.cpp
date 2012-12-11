#include "LobbyState.h"
#include "GameState.h"
#include "Input.h"

LobbyState::LobbyState()
{

}

LobbyState::~LobbyState()
{

}

State* LobbyState::nextState()
{
	return new GameState();
}

void LobbyState::update(float _dt)
{
	if(g_mouse->isRButtonPressed())
	{
		this->setDone(true);
	}
}