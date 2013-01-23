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

	virtual void activate(FLOAT3 position, unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};