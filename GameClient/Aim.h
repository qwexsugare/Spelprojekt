#pragma once

#include "Skill.h"
#include "EntityHandler.h"

class Aim : public Skill
{
private:
	unsigned int m_senderId;
public:
	Aim();
	~Aim();

	bool activate(unsigned int _senderId);
	void updateSpecificSkill(float dt);
};

