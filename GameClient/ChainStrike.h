#pragma once

#include "Skill.h"

class ChainStrike : public Skill
{
private:
	static const float COOLDOWN;
	static const int RANGE = 20;
public:
	ChainStrike();
	~ChainStrike();

	virtual void activate(unsigned int _targetId, unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};