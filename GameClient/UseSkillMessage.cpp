#include "UseSkillMessage.h"

UseSkillMessage::UseSkillMessage()
{

}

UseSkillMessage::UseSkillMessage(unsigned int _skillId, unsigned int _targetId)
{
	m_skillId = _skillId;
	m_targetId = _targetId;
}

UseSkillMessage::~UseSkillMessage()
{

}

sf::Packet& operator<<(sf::Packet& packet, const UseSkillMessage& e)
{
	return packet<<"USE_SKILL"<<e.m_skillId<<e.m_targetId;
}

sf::Packet& operator>>(sf::Packet& packet, UseSkillMessage& e)
{
	return packet>>e.m_skillId>>e.m_targetId;
}