#pragma once

#include "Skill.h"

class EnigmaticPresence : public Skill
{
public:
	EnigmaticPresence();
	~EnigmaticPresence();

	virtual bool activate(unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};