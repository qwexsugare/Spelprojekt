#include "NetworkUseActionPositionMessage.h"

NetworkUseActionPositionMessage::NetworkUseActionPositionMessage() : NetworkMessage()
{

}

NetworkUseActionPositionMessage::NetworkUseActionPositionMessage(unsigned int _actionId, FLOAT3 _position) : NetworkMessage(MESSAGE_TYPE::UseActionPos)
{
	this->m_actionId = _actionId;
	this->m_position = _position;
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

sf::Packet& operator<<(sf::Packet& packet,const NetworkUseActionPositionMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_position.x<<e.m_position.y<<e.m_position.z;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkUseActionPositionMessage& e)
{
	return packet>>e.m_actionId>>e.m_position.x>>e.m_position.y>>e.m_position.z;
}