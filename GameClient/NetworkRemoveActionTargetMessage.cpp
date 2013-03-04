#include "NetworkRemoveActionTargetMessage.h"

NetworkRemoveActionTargetMessage::NetworkRemoveActionTargetMessage() : NetworkMessage()
{

}

NetworkRemoveActionTargetMessage::NetworkRemoveActionTargetMessage(unsigned int _actionId, unsigned int _targetId) : NetworkMessage(NetworkMessage::RemoveActionTarget)
{
	this->m_actionId = _actionId;
	this->m_targetId = _targetId;
}

NetworkRemoveActionTargetMessage::~NetworkRemoveActionTargetMessage()
{

}

unsigned int NetworkRemoveActionTargetMessage::getActionId()
{
	return this->m_actionId;
}

unsigned int NetworkRemoveActionTargetMessage::getTargetId()
{
	return this->m_targetId;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkRemoveActionTargetMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_targetId;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkRemoveActionTargetMessage& e)
{
	return packet>>e.m_actionId>>e.m_targetId;
}