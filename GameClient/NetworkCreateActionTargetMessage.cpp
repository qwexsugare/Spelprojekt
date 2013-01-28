#include "NetworkCreateActionTargetMessage.h"

NetworkCreateActionTargetMessage::NetworkCreateActionTargetMessage() : NetworkMessage()
{

}

NetworkCreateActionTargetMessage::NetworkCreateActionTargetMessage(unsigned int _actionId, unsigned int _senderId, unsigned int _targetId, FLOAT3 _position) : NetworkMessage(MESSAGE_TYPE::CreateActionTarget)
{
	this->m_actionId = _actionId;
	this->m_senderId = _senderId;
	this->m_targetId = _targetId;
	this->m_position = _position;
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

sf::Packet& operator<<(sf::Packet& packet,const NetworkCreateActionTargetMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_senderId<<e.m_targetId;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkCreateActionTargetMessage& e)
{
	return packet>>e.m_actionId>>e.m_senderId>>e.m_targetId;
}