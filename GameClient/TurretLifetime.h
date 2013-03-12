#pragma once

#include "skill.h"
#include "EntityHandler.h"

class TurretLifetime : public Skill
{
private:
	unsigned int m_senderId;
public:
	static const unsigned int COST = 3500;

	TurretLifetime();
	~TurretLifetime();

	bool activate(unsigned int _senderId);
	void updateSpecificSkill(float _dt);
	int getCost();
};