#pragma once

#include "skill.h"
#include "EntityHandler.h"

class Greed : public Skill
{
private:
	unsigned int m_senderId;
public:
	Greed();
	~Greed();

	void activate(unsigned int _senderId);
};

