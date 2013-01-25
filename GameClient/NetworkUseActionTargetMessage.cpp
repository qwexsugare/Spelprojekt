#include "NetworkUseActionTargetMessage.h"

NetworkUseActionTargetMessage::NetworkUseActionTargetMessage() : NetworkMessage()
{

}

NetworkUseActionTargetMessage::NetworkUseActionTargetMessage(unsigned int _actionId, unsigned int _targetId) : NetworkMessage(MESSAGE_TYPE::UseActionTarget)
{
	this->m_actionId = _actionId;
	this->m_targetId = _targetId;
}

NetworkUseActionTargetMessage::~NetworkUseActionTargetMessage()
{

}

unsigned int NetworkUseActionTargetMessage::getActionId()
{
	return this->m_actionId;
}

unsigned int NetworkUseActionTargetMessage::getTargetId()
{
	return this->m_targetId;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkUseActionTargetMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_targetId;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkUseActionTargetMessage& e)
{
	return packet>>e.m_actionId>>e.m_targetId;
}