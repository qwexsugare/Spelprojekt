#include "NetworkUpdateEntityHealth.h"


NetworkUpdateEntityHealth::NetworkUpdateEntityHealth(void): NetworkMessage()
{
	this->m_id=0;
	this->health=0;
}


NetworkUpdateEntityHealth::~NetworkUpdateEntityHealth(void)
{
}
NetworkUpdateEntityHealth::NetworkUpdateEntityHealth(int id, int health): NetworkMessage(MESSAGE_TYPE::updateEntityHealth)
{
	this->m_id=id;
	this->health=health;
}
int NetworkUpdateEntityHealth::getHealth()
{
	return this->health;
}
int NetworkUpdateEntityHealth::getId()
{
	return this->m_id;
}
sf::Packet& operator<<(sf::Packet& packet,const NetworkUpdateEntityHealth& e)
{
	return packet << *((int*)&e.m_type)<<e.m_id<<e.health;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkUpdateEntityHealth& e)
{
	return packet>>e.m_id>>e.health;
}