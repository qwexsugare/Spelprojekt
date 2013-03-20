#pragma once

#include "clientskilleffect.h"
#include "Model.h"

class EnigmaticPresenceClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_masterId;
	bool m_active;
	ParticleEngine* m_aura;
public:
	EnigmaticPresenceClientSkillEffect(unsigned int _masterId);
	~EnigmaticPresenceClientSkillEffect();

	bool getActive();
	int getMasterId()const { return m_masterId; }
	void update(float _dt);
};