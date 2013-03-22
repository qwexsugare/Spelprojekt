#pragma once
#include "clientskilleffect.h"
class TargetAcquiredClientSkillEffect : public ClientSkillEffect
{
private:
	float m_lifetime;
	ParticleEngine* m_fire;
	ParticleEngine* m_fireTwo;
	ParticleEngine* m_ice;
	ParticleEngine* m_lightning;
	FLOAT3 m_firePos;
	FLOAT3 m_fireTwoPos;
	FLOAT3 m_icePos;
	FLOAT3 m_lightningPos;
	bool m_bfireOne, m_bfireTwo, m_biceOne, m_blightningOne;
public:
	TargetAcquiredClientSkillEffect(unsigned int _masterId, FLOAT3 position);
	~TargetAcquiredClientSkillEffect();

	void update(float _dt);
	bool getActive();
};

