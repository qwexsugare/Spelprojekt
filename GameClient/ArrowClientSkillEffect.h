#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"
#include "Hero.h"

class ArrowClientSkillEffect : public ClientSkillEffect
{
private:
	Model* m_graphicalEffect;
	unsigned int m_targetId;
	unsigned int m_masterId;
	float m_aimTime;
	bool m_active;
	ParticleEngine* m_particleSystem;
public:
	ArrowClientSkillEffect(FLOAT3 _position, unsigned int _targetId, unsigned int _masterId, float _animationSpeed);
	~ArrowClientSkillEffect();

	void update(float _dt);
	bool getActive();
};