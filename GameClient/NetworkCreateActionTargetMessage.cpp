#include "NetworkCreateActionTargetMessage.h"

NetworkCreateActionTargetMessage::NetworkCreateActionTargetMessage() : NetworkMessage()
{

}

NetworkCreateActionTargetMessage::NetworkCreateActionTargetMessage(unsigned int _actionId, unsigned int _senderId, unsigned int _targetId, FLOAT3 _position, float _animationSpeed) : NetworkMessage(MESSAGE_TYPE::CreateActionTarget)
{
	this->m_actionId = _actionId;
	this->m_senderId = _senderId;
	this->m_targetId = _targetId;
	this->m_position = _position;
	this->m_animationSpeed = _animationSpeed;
}

NetworkCreateActionTargetMessage::~NetworkCreateActionTargetMessage(void)
{

}

unsigned int NetworkCreateActionTargetMessage::getActionId()
{
	return this->m_actionId;
}

unsigned int NetworkCreateActionTargetMessage::getSenderId()
{
	return this->m_senderId;
}

unsigned int NetworkCreateActionTargetMessage::getTargetId()
{
	return this->m_targetId;
}

FLOAT3 NetworkCreateActionTargetMessage::getPosition()
{
	return this->m_position;
}

float NetworkCreateActionTargetMessage::getAnimationSpeed()
{
	return this->m_animationSpeed;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkCreateActionTargetMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_senderId<<e.m_targetId<<e.m_position.x<<e.m_position.y<<e.m_position.z<<e.m_animationSpeed;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkCreateActionTargetMessage& e)
{
	return packet>>e.m_actionId>>e.m_senderId>>e.m_targetId>>e.m_position.x>>e.m_position.y>>e.m_position.z>>e.m_animationSpeed;
}