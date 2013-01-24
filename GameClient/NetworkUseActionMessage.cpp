#include "NetworkUseActionMessage.h"

NetworkUseActionMessage::NetworkUseActionMessage()
{

}

NetworkUseActionMessage::NetworkUseActionMessage(unsigned int _actionId) : NetworkMessage(MESSAGE_TYPE::UseAction)
{
	this->m_actionId = _actionId;
}

NetworkUseActionMessage::~NetworkUseActionMessage()
{

}

unsigned int NetworkUseActionMessage::getActionId()
{
	return this->m_actionId;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkUseActionMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkUseActionMessage& e)
{
	return packet>>e.m_actionId;
}