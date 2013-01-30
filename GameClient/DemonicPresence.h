#pragma once

#include "Skill.h"

class DemonicPresence : public Skill
{
private:
	static const float COOLDOWN;
public:
	DemonicPresence();
	~DemonicPresence();

	virtual bool activate(unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};