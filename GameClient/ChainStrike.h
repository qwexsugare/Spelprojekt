#pragma once

#include "Skill.h"

class ChainStrike : public Skill
{
private:
	static const float COOLDOWN;
	static const int RANGE = 20;
public:
	static const unsigned int COST = 2500;
	static const int START_DAMAGE = 200;

	ChainStrike();
	~ChainStrike();

	virtual bool activate(unsigned int _targetId, unsigned int _senderId);
	void updateSpecificSkill(float _dt);
	int getCost();
};