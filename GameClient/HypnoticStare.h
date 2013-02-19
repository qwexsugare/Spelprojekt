#pragma once

#include "Skill.h"

class HypnoticStare : public Skill
{
private:
	static const float COOLDOWN;
	static const int RANGE = 10;
public:
	static const float TIME_FACTOR;

	HypnoticStare();
	~HypnoticStare();

	virtual bool activate(unsigned int _senderId, unsigned int _targetId);
	void updateSpecificSkill(float _dt);
};