#include "NetworkCreateActionTargetMessage.h"

NetworkCreateActionTargetMessage::NetworkCreateActionTargetMessage() : NetworkMessage()
{

}

NetworkCreateActionTargetMessage::NetworkCreateActionTargetMessage(unsigned int _actionId, unsigned int _senderId, unsigned int _targetId) : NetworkMessage(MESSAGE_TYPE::CreateActionTarget)
{
	this->m_actionId = _actionId;
	this->m_senderId = _senderId;
	this->m_targetId = _targetId;
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

sf::Packet& operator<<(sf::Packet& packet,const NetworkCreateActionTargetMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_senderId<<e.m_targetId;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkCreateActionTargetMessage& e)
{
	return packet>>e.m_actionId>>e.m_senderId>>e.m_targetId;
}