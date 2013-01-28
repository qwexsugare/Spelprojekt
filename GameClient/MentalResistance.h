#pragma once

#include "skill.h"
#include "EntityHandler.h"

class MentalResistance : public Skill
{
private:
	unsigned int m_senderId;
public:
	MentalResistance();
	~MentalResistance();

	void activate(unsigned int _senderId);
};

