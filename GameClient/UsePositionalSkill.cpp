#include "UsePositionalSkill.h"

UsePositionalSkill::UsePositionalSkill()
{

}

UsePositionalSkill::UsePositionalSkill(unsigned int _skillId, FLOAT3 _pos)
{
	m_skillId = _skillId;
	m_pos = _pos;
}

UsePositionalSkill::~UsePositionalSkill()
{

}

sf::Packet& operator<<(sf::Packet& packet, const UsePositionalSkill& e)
{
	//return packet<<"USE_SKILL"<<e.m_skillId<<e.m_targetId;
}

sf::Packet& operator>>(sf::Packet& packet, UsePositionalSkill& e)
{
	//return packet>>e.m_skillId>>e.m_targetId;
}