#pragma once

#include "Skill.h"

class CloudOfDarkness : public Skill
{
private:
	static const float COOLDOWN;
	static const int RANGE = 20;
public:
	CloudOfDarkness();
	~CloudOfDarkness();

	virtual void activate(unsigned int _targetId, unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};