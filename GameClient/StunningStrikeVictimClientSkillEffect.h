#pragma once

#include "clientskilleffect.h"
#include "ClientEntityHandler.h"

class StunningStrikeVictimClientSkillEffect : public ClientSkillEffect
{
private:
	float m_lifetime;
	unsigned int m_masterId;
public:
	StunningStrikeVictimClientSkillEffect(unsigned int _id);
	~StunningStrikeVictimClientSkillEffect();

	void update(float _dt);
	bool getActive();
};

