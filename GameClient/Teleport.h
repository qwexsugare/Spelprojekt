#pragma once

#include "Skill.h"

class Teleport : public Skill
{
private:
	static const float COOLDOWN;
	static const int RANGE = 50;
public:
	static const unsigned int COST = 500;

	Teleport();
	~Teleport();

	virtual bool activate(FLOAT3 _position, unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};