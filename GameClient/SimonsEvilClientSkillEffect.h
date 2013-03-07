#pragma once

#include "clientskilleffect.h"
#include "Model.h"

class SimonsEvilClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_masterId;
	float m_timer;
	ParticleEngine* m_particleSystem;
public:
	SimonsEvilClientSkillEffect(unsigned int _masterId);
	~SimonsEvilClientSkillEffect();

	bool getActive();
	int getMasterId()const { return m_masterId; }
	void update(float _dt);
};