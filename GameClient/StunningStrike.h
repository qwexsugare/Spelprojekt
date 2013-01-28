#pragma once

#include "Skill.h"

class StunningStrike : public Skill
{
private:
	static const float COOLDOWN;
public:
	StunningStrike();
	~StunningStrike();

	virtual bool activate(unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};