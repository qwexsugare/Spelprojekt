#pragma once

#include "skill.h"
#include "EntityHandler.h"
#include "Turret.h"

class TimeIsMoney : public Skill
{
private:
	bool m_active;
public:
	static const float COOLDOWN;

	TimeIsMoney();
	~TimeIsMoney();

	void updateSpecificSkill(float _dt);
	virtual bool activate(unsigned int _senderId);
	bool getActive();
	void setActive(bool _active);
};

