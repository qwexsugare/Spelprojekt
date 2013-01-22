#pragma once

#include <SFML\Network.hpp>

class UseSkillMessage
{
private:
	unsigned int m_skillId;
	unsigned int m_targetId;
public:
	UseSkillMessage();
	UseSkillMessage(unsigned int _skillId, unsigned int _targetId);
	~UseSkillMessage();

	unsigned int getSkillId()const { return m_skillId; }
	unsigned int getTargetId()const { return m_targetId; }

	friend sf::Packet& operator<<(sf::Packet& packet,const UseSkillMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, UseSkillMessage& e);
};

