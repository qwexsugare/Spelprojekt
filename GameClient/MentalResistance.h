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

	bool activate(unsigned int _senderId);
	void updateSpecificSkill(float dt);
};

