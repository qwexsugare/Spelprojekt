#pragma once

#include "skill.h"
#include "EntityHandler.h"
#include "Turret.h"

class EnhancedDevelopment : public Skill
{
private:
	static float RANGE;

	unsigned int m_masterId;
public:
	EnhancedDevelopment();
	~EnhancedDevelopment();

	virtual bool activate(unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};

