#pragma once

#include "skill.h"
#include "EntityHandler.h"
#include "Turret.h"

class ReadyAimFire : public Skill
{
private:
	static float RANGE;

	unsigned int m_senderId;
public:
	ReadyAimFire();
	~ReadyAimFire();

	bool activate(unsigned int _senderId);
	void updateSpecificSkill(float dt);
};

