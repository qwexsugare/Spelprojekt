#pragma once

#include "skill.h"
#include "EntityHandler.h"

class Greed : public Skill
{
private:
	unsigned int m_senderId;
public:
	static const unsigned int COST = 700;

	Greed();
	~Greed();

	bool activate(unsigned int _senderId);
	void updateSpecificSkill(float dt);
};

