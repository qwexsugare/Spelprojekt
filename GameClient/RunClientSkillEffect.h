#pragma once
#include "clientskilleffect.h"
#include "ClientEntityHandler.h"

class RunClientSkillEffect : public ClientSkillEffect
{
public:
	RunClientSkillEffect(unsigned int masterId);
	~RunClientSkillEffect();

	void update(float dt);
	bool getActive();
};

