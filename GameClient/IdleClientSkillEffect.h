#pragma once
#include "clientskilleffect.h"
#include "ClientEntityHandler.h"

class IdleClientSkillEffect : public ClientSkillEffect
{
public:
	IdleClientSkillEffect(unsigned int masterId);
	~IdleClientSkillEffect();

	void update(float dt);
	bool getActive();
};

