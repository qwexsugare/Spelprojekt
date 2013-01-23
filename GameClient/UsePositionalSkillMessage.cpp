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
	float tempX = e.getPos().x;
	float tempY = e.getPos().y;
	float tempZ = e.getPos().z;
	return packet>>e.m_skillId>> tempX >> tempY >> tempZ;
}