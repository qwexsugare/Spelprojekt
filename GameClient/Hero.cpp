#include "Hero.h"

Hero::Hero() : ServerEntity()
{
	this->m_nextPosition = this->m_positon;
	this->m_reachedPosition = true;
	this->m_movementSpeed = 5.0f;
}

void Hero::update(float dt)
{
	if(this->m_reachedPosition == false)
	{
		FLOAT3 distance = this->m_nextPosition - this->m_positon;
		if(distance.length() > this->m_movementSpeed * dt)
		{
			distance = distance / distance.length();
			this->m_positon = this->m_positon + (distance * this->m_movementSpeed * dt);
		}
		else
		{
			this->m_positon = this->m_nextPosition;
			this->m_reachedPosition = true;
		}

		this->m_rotation.x = atan2(-distance.x, -distance.z);
	}
}

void Hero::setNextPosition(FLOAT3 _nextPosition)
{
	this->m_nextPosition = _nextPosition;
	this->m_reachedPosition = false;
}