#pragma once

#include <SFML\Network.hpp>
#include "Datastructures.h"

class UsePositionalSkillMessage
{
private:
	unsigned int m_skillId;
	FLOAT3 m_pos;
public:
	UsePositionalSkillMessage();
	UsePositionalSkillMessage(unsigned int _skillId, FLOAT3 _pos);
	~UsePositionalSkillMessage();

	unsigned int getSkillId()const { return m_skillId; }
	const FLOAT3& getPos()const { return m_pos; }

	friend sf::Packet& operator<<(sf::Packet& packet,const UsePositionalSkillMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, UsePositionalSkillMessage& e);
};