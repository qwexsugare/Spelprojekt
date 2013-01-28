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

	void activate(unsigned int _senderId);
};

