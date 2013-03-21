#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"
#include "Hero.h"

class PoisonTurretProjectileClientSkillEffect : public ClientSkillEffect
{
private:
	Model* m_graphicalEffect;
	unsigned int m_targetId;
	bool m_active;
	ParticleEngine* m_pe;
	FLOAT3 m_position;
public:
	PoisonTurretProjectileClientSkillEffect(FLOAT3 _position, unsigned int _targetId);
	~PoisonTurretProjectileClientSkillEffect();

	void update(float _dt);
	bool getActive();
};