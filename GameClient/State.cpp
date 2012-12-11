#include "State.h"

State::State()
{
	this->m_done = false;
}

State::~State()
{

}

bool State::isDone()
{
	return this->m_done;
}

void State::setDone(bool _done)
{
	this->m_done = _done;
}