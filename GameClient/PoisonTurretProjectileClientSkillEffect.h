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
public:
	PoisonTurretProjectileClientSkillEffect(FLOAT3 _position, unsigned int _targetId);
	~PoisonTurretProjectileClientSkillEffect();

	void update(float _dt);
	bool getActive();
};