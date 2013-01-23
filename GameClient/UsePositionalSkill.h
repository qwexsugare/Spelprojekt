#pragma once

#include <SFML\Network.hpp>
#include "Datastructures.h"

class UsePositionalSkill
{
private:
	unsigned int m_skillId;
	FLOAT3 m_pos;
public:
	UsePositionalSkill();
	UsePositionalSkill(unsigned int _skillId, FLOAT3 _pos);
	~UsePositionalSkill();

	unsigned int getSkillId()const { return m_skillId; }
	const FLOAT3& getPos()const { return m_pos; }

	friend sf::Packet& operator<<(sf::Packet& packet,const UsePositionalSkill& e);
	friend sf::Packet& operator>>(sf::Packet& packet, UsePositionalSkill& e);
};