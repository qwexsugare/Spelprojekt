#include "NetworkSkillUsedMessage.h"

NetworkSkillUsedMessage::NetworkSkillUsedMessage()
{

}

NetworkSkillUsedMessage::NetworkSkillUsedMessage(unsigned int _actionId, unsigned int _actionIndex, float _cooldown) : NetworkMessage(NetworkMessage::SkillUsed)
{
	this->m_actionId = _actionId;
	this->m_actionIndex = _actionIndex;
	this->m_cooldown = _cooldown;
}

NetworkSkillUsedMessage::~NetworkSkillUsedMessage(void)
{

}

unsigned int NetworkSkillUsedMessage::getActionId()
{
	return this->m_actionId;
}

unsigned int NetworkSkillUsedMessage::getActionIndex()
{
	return this->m_actionIndex;
}

float NetworkSkillUsedMessage::getCooldown()
{
	return this->m_cooldown;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkSkillUsedMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_actionIndex<<e.m_cooldown;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkSkillUsedMessage& e)
{
	return packet>>e.m_actionId>>e.m_actionIndex>>e.m_cooldown;
}