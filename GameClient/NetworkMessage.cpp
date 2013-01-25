#include "NetworkMessage.h"

NetworkMessage::NetworkMessage()
{

}

NetworkMessage::NetworkMessage(MESSAGE_TYPE _type)
{
	this->m_type = _type;
}

NetworkMessage::MESSAGE_TYPE NetworkMessage::getType()
{
	return this->m_type;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkMessage& e)
{
	return packet<<*((int*)&e.m_type);

}

sf::Packet& operator>>(sf::Packet& packet, NetworkMessage& e)
{
	return packet>>*((int*)&e.m_type);
}