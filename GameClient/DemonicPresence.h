#pragma once

#include "Skill.h"

class DemonicPresence : public Skill
{
private:
	static const float COOLDOWN;
public:
	static const int COST = 4000;

	DemonicPresence();
	~DemonicPresence();

	virtual bool activate(unsigned int _senderId);
	void updateSpecificSkill(float _dt);
	int getCost();
};