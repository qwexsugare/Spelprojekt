#pragma once

#include "Skill.h"

class LifeRegen : public Skill
{
public:
	LifeRegen();
	~LifeRegen();

	virtual bool activate(unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};