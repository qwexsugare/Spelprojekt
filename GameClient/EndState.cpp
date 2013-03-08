#include "EndState.h"
#include "Graphics.h"

EndState::EndState(bool _victorious)
{

}

EndState::~EndState()
{

}

State::StateEnum EndState::nextState()
{
	return State::MAIN_MENU;
}

void EndState::update(float _dt)
{
	int dbg = 1;
}