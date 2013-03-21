#pragma once

#include "clientskilleffect.h"
#include "ClientEntityHandler.h"

class HealingFountainClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_id;
	float m_lifetime;
	ParticleEngine* m_heal;
public:
	HealingFountainClientSkillEffect(unsigned int _id);
	~HealingFountainClientSkillEffect();

	void update(float _dt);
	bool getActive();
};

