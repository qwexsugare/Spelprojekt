#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"
#include "Hero.h"

class FrostTurretProjectileClientSkillEffect : public ClientSkillEffect
{
private:
	Model* m_graphicalEffect;
	unsigned int m_targetId;
	bool m_active;
	ParticleEngine* m_pe[2];
public:
	FrostTurretProjectileClientSkillEffect(FLOAT3 _position, unsigned int _targetId);
	~FrostTurretProjectileClientSkillEffect();

	void update(float _dt);
	bool getActive();
};