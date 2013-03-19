#pragma once

#include "Skill.h"

class HypnoticStare : public Skill
{
private:
	static const float COOLDOWN;
	static const int RANGE = 10;
public:
	HypnoticStare();
	~HypnoticStare();

	virtual bool activate(unsigned int _senderId, unsigned int _targetId);
	void updateSpecificSkill(float _dt);
};