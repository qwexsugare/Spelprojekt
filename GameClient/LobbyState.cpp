#include "LobbyState.h"
#include "GameState.h"

LobbyState::LobbyState()
{

}

LobbyState::~LobbyState()
{

}

bool LobbyState::done()
{
	return false;
}

State* LobbyState::nextState()
{
	return new GameState();
}

void LobbyState::update(float _dt)
{
	
}