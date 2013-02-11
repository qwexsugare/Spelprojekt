#pragma once

#include "Skill.h"

class SimonsEvil : public Skill
{
private:
	static const float COOLDOWN;
public:

	SimonsEvil();
	~SimonsEvil();

	virtual bool activate(unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};