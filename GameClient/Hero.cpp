#include "Hero.h"

Hero::Hero() : ServerEntity()
{
	this->m_nextPosition = this->m_positon;
	this->m_reachedPosition = true;
	this->m_movementSpeed = 0.0005f;
}

void Hero::update()
{
	if(this->m_reachedPosition == false)
	{
		FLOAT3 distance = this->m_nextPosition - this->m_positon;

		if(distance.length() > this->m_movementSpeed)
		{
			distance = distance / distance.length();
			this->m_positon = this->m_positon + (distance * this->m_movementSpeed);
		}
		else
		{
			this->m_positon = this->m_nextPosition;
			this->m_reachedPosition = true;
		}
	}
}

void Hero::setNextPosition(FLOAT3 _nextPosition)
{
	this->m_nextPosition = _nextPosition;
	this->m_reachedPosition = false;
}