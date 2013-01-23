#include "RemoveEntityMessage.h"

RemoveEntityMessage::RemoveEntityMessage()
{
	this->m_id = 0;
}

RemoveEntityMessage::RemoveEntityMessage(unsigned int _id)
{
	this->m_id = _id;
}

RemoveEntityMessage::~RemoveEntityMessage()
{

}

void RemoveEntityMessage::setId(unsigned int _id)
{
	this->m_id = _id;
}

unsigned int RemoveEntityMessage::getId()
{
	return this->m_id;
}

sf::Packet& operator<<(sf::Packet& packet,const RemoveEntityMessage& e)
{
	return packet<<"REMOVE"<<e.m_id;
}

sf::Packet& operator>>(sf::Packet& packet, RemoveEntityMessage& e)
{
	return packet >>e.m_id;
}