#include "NetworkUseActionPositionMessage.h"

NetworkUseActionPositionMessage::NetworkUseActionPositionMessage() : NetworkMessage()
{

}

NetworkUseActionPositionMessage::NetworkUseActionPositionMessage(unsigned int _actionId, FLOAT3 _position, unsigned int _index) : NetworkMessage(MESSAGE_TYPE::UseActionPos)
{
	this->m_actionId = _actionId;
	this->m_position = _position;
	this->m_index = _index;
}

NetworkUseActionPositionMessage::~NetworkUseActionPositionMessage()
{

}

unsigned int NetworkUseActionPositionMessage::getActionId()
{
	return this->m_actionId;
}

FLOAT3 NetworkUseActionPositionMessage::getPosition()
{
	return this->m_position;
}

unsigned int NetworkUseActionPositionMessage::getIndex()
{
	return this->m_index;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkUseActionPositionMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_position.x<<e.m_position.y<<e.m_position.z<<e.m_index;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkUseActionPositionMessage& e)
{
	return packet>>e.m_actionId>>e.m_position.x>>e.m_position.y>>e.m_position.z>>e.m_index;
}