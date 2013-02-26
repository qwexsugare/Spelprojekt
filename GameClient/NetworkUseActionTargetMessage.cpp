#include "NetworkUseActionTargetMessage.h"

NetworkUseActionTargetMessage::NetworkUseActionTargetMessage() : NetworkMessage()
{

}

NetworkUseActionTargetMessage::NetworkUseActionTargetMessage(unsigned int _actionId, unsigned int _targetId, unsigned int _index) : NetworkMessage(MESSAGE_TYPE::UseActionTarget)
{
	this->m_actionId = _actionId;
	this->m_targetId = _targetId;
	this->m_index = _index;
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

unsigned int NetworkUseActionTargetMessage::getIndex()
{
	return this->m_index;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkUseActionTargetMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_targetId<<e.m_index;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkUseActionTargetMessage& e)
{
	return packet>>e.m_actionId>>e.m_targetId>>e.m_index;
}