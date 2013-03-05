#pragma once

#include "Skill.h"
#include "EntityHandler.h"
#include "WallEffect.h"

class Wall : public Skill
{
public:
	static const int COST = 4000;
	static const float COOLDOWN;

	Wall();
	~Wall();

	virtual bool activate(FLOAT3 _position, unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};

