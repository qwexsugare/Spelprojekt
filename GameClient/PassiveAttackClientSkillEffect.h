#pragma once

#include "clientskilleffect.h"
#include "ClientEntityHandler.h"
#include "ModelIdHolder.h"

class PassiveAttackClientSkillEffect : public ClientSkillEffect
{
public:
	PassiveAttackClientSkillEffect(unsigned int _masterId);
	~PassiveAttackClientSkillEffect();

	void update(float dt);
	bool getActive();
};

