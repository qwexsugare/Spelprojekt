#include "NetworkSkillBoughtMessage.h"

NetworkSkillBoughtMessage::NetworkSkillBoughtMessage()
{

}

NetworkSkillBoughtMessage::NetworkSkillBoughtMessage(unsigned int _actionId, unsigned int _resources) : NetworkMessage(MESSAGE_TYPE::SkillBought)
{
	this->m_actionId = _actionId;
	this->m_resources = _resources;
}

NetworkSkillBoughtMessage::~NetworkSkillBoughtMessage()
{

}

unsigned int NetworkSkillBoughtMessage::getActionId()
{
	return this->m_actionId;
}

unsigned int NetworkSkillBoughtMessage::getResources()
{
	return this->m_resources;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkSkillBoughtMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId<<e.m_resources;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkSkillBoughtMessage& e)
{
	return packet>>e.m_actionId>>e.m_resources;
}