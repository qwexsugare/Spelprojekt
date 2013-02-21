#pragma once

#include "clientskilleffect.h"
#include "ClientEntityHandler.h"

class MeleeAttackClientSkillEffect : public ClientSkillEffect
{
private:
	int m_lifetime;
public:
	MeleeAttackClientSkillEffect(unsigned int masterId);
	~MeleeAttackClientSkillEffect();

	void update(float dt);
	bool getActive();
};