#include "NetworkRemoveActionTargetMessage.h"

NetworkRemoveActionTargetMessage::NetworkRemoveActionTargetMessage() : NetworkMessage()
{

}

NetworkRemoveActionTargetMessage::NetworkRemoveActionTargetMessage(unsigned int _actionId, unsigned int _targetId, FLOAT3 _position) : NetworkMessage(NetworkMessage::RemoveActionTarget)
{
	this->m_actionId = _actionId;
	this->m_targetId = _targetId;
	m_position = _position;
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

FLOAT3 NetworkRemoveActionTargetMessage::getPosition()
{
	return this->m_position;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkRemoveActionTargetMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_targetId<<e.m_position.x<<e.m_position.y<<e.m_position.z;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkRemoveActionTargetMessage& e)
{
	return packet>>e.m_actionId>>e.m_targetId>>e.m_position.x>>e.m_position.y>>e.m_position.z;
}