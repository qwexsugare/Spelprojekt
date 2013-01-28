#include "NetworkCreateActionPositionMessage.h"

NetworkCreateActionPositionMessage::NetworkCreateActionPositionMessage() : NetworkMessage()
{

}

NetworkCreateActionPositionMessage::NetworkCreateActionPositionMessage(unsigned int _actionId, unsigned int _senderId, FLOAT3 _position) : NetworkMessage(MESSAGE_TYPE::CreateActionPos)
{
	this->m_actionId = _actionId;
	this->m_senderId = _senderId;
	this->m_position = _position;
}

NetworkCreateActionPositionMessage::~NetworkCreateActionPositionMessage()
{

}

unsigned int NetworkCreateActionPositionMessage::getActionId()
{
	return this->m_actionId;
}

unsigned int NetworkCreateActionPositionMessage::getSenderId()
{
	return this->m_senderId;
}

FLOAT3 NetworkCreateActionPositionMessage::getPosition()
{
	return this->m_position;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkCreateActionPositionMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_senderId<<e.m_position.x<<e.m_position.y<<e.m_position.z;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkCreateActionPositionMessage& e)
{
	return packet>>e.m_actionId>>e.m_senderId>>e.m_position.x>>e.m_position.y>>e.m_position.z;
}