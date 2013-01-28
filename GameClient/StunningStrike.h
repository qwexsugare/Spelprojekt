#pragma once

#include "Skill.h"

class StunningStrike : public Skill
{
private:
	static const float COOLDOWN;
public:
	StunningStrike();
	~StunningStrike();

	virtual void activate(unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};