#pragma once

#include "skill.h"
#include "EntityHandler.h"

class MentalResistance : public Skill
{
private:
	unsigned int m_senderId;
public:
	static const unsigned int COST = 900;

	MentalResistance();
	~MentalResistance();

	bool activate(unsigned int _senderId);
	void updateSpecificSkill(float dt);
};

