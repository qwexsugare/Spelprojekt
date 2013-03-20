#pragma once

#include "clientskilleffect.h"
#include "ParticleEngine.h"

class CourageHonorValorClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_masterId;
	Model* m_model;
	float m_soundTimer;
	bool m_hasSpoken;
	bool m_active;
	ParticleEngine* m_aura;
public:
	CourageHonorValorClientSkillEffect(unsigned int _masterId, unsigned int _redKnightId);
	~CourageHonorValorClientSkillEffect();

	bool getActive();
	int getMasterId()const { return m_masterId; }
	void update(float _dt);
};