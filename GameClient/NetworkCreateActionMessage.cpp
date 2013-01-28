#include "NetworkCreateActionMessage.h"

NetworkCreateActionMessage::NetworkCreateActionMessage() : NetworkMessage()
{

}

NetworkCreateActionMessage::NetworkCreateActionMessage(unsigned int _actionId, unsigned int _senderId, FLOAT3 _position) : NetworkMessage(MESSAGE_TYPE::CreateAction)
{
	this->m_actionId = _actionId;
	this->m_senderId = _senderId;
	this->m_position = _position;
}

NetworkCreateActionMessage::~NetworkCreateActionMessage()
{

}

unsigned int NetworkCreateActionMessage::getActionId()
{
	return this->m_actionId;
}

unsigned int NetworkCreateActionMessage::getSenderId()
{
	return this->m_senderId;
}

FLOAT3 NetworkCreateActionMessage::getPosition()
{
	return this->m_position;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkCreateActionMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_senderId;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkCreateActionMessage& e)
{
	return packet>>e.m_actionId>>e.m_senderId;
}