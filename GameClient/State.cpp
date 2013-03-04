#include "State.h"

State::State()
{
	this->m_done = false;
}

State::State(StateEnum _type)
{
	this->m_type = _type;
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

State::StateEnum State::getType()
{
	return this->m_type;
}