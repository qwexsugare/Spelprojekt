#include "NetworkCreateActionMessage.h"

NetworkCreateActionMessage::NetworkCreateActionMessage() : NetworkMessage()
{

}

NetworkCreateActionMessage::NetworkCreateActionMessage(unsigned int _actionId, unsigned int _senderId, FLOAT3 _position, float _animationSpeed) : NetworkMessage(MESSAGE_TYPE::CreateAction)
{
	this->m_actionId = _actionId;
	this->m_senderId = _senderId;
	this->m_position = _position;
	this->m_animationSpeed = _animationSpeed;
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

float NetworkCreateActionMessage::getAnimationSpeed()
{
	return this->m_animationSpeed;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkCreateActionMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_senderId<<e.m_position.x<<e.m_position.y<<e.m_position.z<<e.m_animationSpeed;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkCreateActionMessage& e)
{
	return packet>>e.m_actionId>>e.m_senderId>>e.m_position.x>>e.m_position.y>>e.m_position.z>>e.m_animationSpeed;
}