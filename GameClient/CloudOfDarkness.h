#pragma once

#include "Skill.h"

class CloudOfDarkness : public Skill
{
private:
	static const float COOLDOWN;
	static const int RANGE = 5;
public:
	CloudOfDarkness();
	~CloudOfDarkness();

	virtual bool activate(FLOAT3 _position, unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};