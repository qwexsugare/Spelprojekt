#pragma once

#include "skill.h"
#include "EntityHandler.h"

class TurretDamage : public Skill
{
private:
	unsigned int m_senderId;
public:
	static const unsigned int COST = 3500;

	TurretDamage();
	~TurretDamage();

	bool activate(unsigned int _senderId);
	void updateSpecificSkill(float _dt);
	int getCost();
};