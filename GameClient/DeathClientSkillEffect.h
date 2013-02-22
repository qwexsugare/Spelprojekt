#pragma once

#include "clientskilleffect.h"
#include "ClientEntityHandler.h"

class DeathClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_masterId;
	Model *m_model;
	float m_lifetime;
public:
	DeathClientSkillEffect(unsigned int _masterId);
	~DeathClientSkillEffect();

	void update(float dt);
	bool getActive();
};

