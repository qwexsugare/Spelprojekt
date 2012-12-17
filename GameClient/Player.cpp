#include "Player.h"

Player::Player(unsigned int id)
{
	this->m_id = id;
	this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
}

void Player::handleEntityMessage(EntityMessage e)
{
	this->m_position = e.getPos();
}

EntityMessage Player::getUpdate()
{
	EntityMessage e = EntityMessage(this->m_id);
	e.setPosition(this->m_position);

	return e;
}