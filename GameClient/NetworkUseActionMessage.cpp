#include "NetworkUseActionMessage.h"

NetworkUseActionMessage::NetworkUseActionMessage()
{

}

NetworkUseActionMessage::NetworkUseActionMessage(unsigned int _actionId, unsigned int _index) : NetworkMessage(MESSAGE_TYPE::UseAction)
{
	this->m_actionId = _actionId;
	this->m_index = _index;
}

NetworkUseActionMessage::~NetworkUseActionMessage()
{

}

unsigned int NetworkUseActionMessage::getActionId()
{
	return this->m_actionId;
}

unsigned int NetworkUseActionMessage::getIndex()
{
	return this->m_index;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkUseActionMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_index;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkUseActionMessage& e)
{
	return packet>>e.m_actionId>>e.m_index;
}