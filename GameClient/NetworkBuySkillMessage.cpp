#include "NetworkBuySkillMessage.h"

NetworkBuySkillMessage::NetworkBuySkillMessage()
{

}

NetworkBuySkillMessage::NetworkBuySkillMessage(unsigned int _actionId) : NetworkMessage(MESSAGE_TYPE::BuySkill)
{
	this->m_actionId = _actionId;
}

NetworkBuySkillMessage::~NetworkBuySkillMessage()
{

}

unsigned int NetworkBuySkillMessage::getActionId()
{
	return this->m_actionId;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkBuySkillMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_actionId;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkBuySkillMessage& e)
{
	return packet>>e.m_actionId;
}