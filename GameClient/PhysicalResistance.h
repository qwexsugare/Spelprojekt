#pragma once

#include "skill.h"
#include "EntityHandler.h"

class PhysicalResistance : public Skill
{
private:
	unsigned int m_senderId;
public:
	static const unsigned int COST = 900;

	PhysicalResistance(unsigned int _senderId);
	~PhysicalResistance();

	void updateSpecificSkill(float dt);
	int getCost();
};

