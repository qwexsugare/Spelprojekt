#pragma once

#include "skill.h"
#include "EntityHandler.h"

class PhysicalResistance : public Skill
{
private:
	unsigned int m_senderId;
public:
	PhysicalResistance();
	~PhysicalResistance();

	void activate(unsigned int _senderId);
};

