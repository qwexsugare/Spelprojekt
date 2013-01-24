#include "UsePositionalSkillMessage.h"

UsePositionalSkillMessage::UsePositionalSkillMessage()
{

}

UsePositionalSkillMessage::UsePositionalSkillMessage(unsigned int _skillId, FLOAT3 _pos)
{
	m_skillId = _skillId;
	m_pos = _pos;
}

UsePositionalSkillMessage::~UsePositionalSkillMessage()
{

}

sf::Packet& operator<<(sf::Packet& packet, const UsePositionalSkillMessage& e)
{
	return packet<<"USE_POSITIONAL_SKILL"<<e.m_skillId<< e.getPos().x << e.getPos().y << e.getPos().z;
}

sf::Packet& operator>>(sf::Packet& packet, UsePositionalSkillMessage& e)
{
	return packet>>e.m_skillId>> e.m_pos.x >> e.m_pos.y >> e.m_pos.z;
}