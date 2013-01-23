#pragma once

#include "Skill.h"

class ChainStrike : public Skill
{
public:
	ChainStrike();
	~ChainStrike();

	virtual void activate(unsigned int _targetId);
	void updateSpecificSkill(float _dt);
};