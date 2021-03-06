#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"
#include "PointLight.h"
#include "ClientEntityHandler.h"

class ChainStrikeClientSkillEffect : public ClientSkillEffect
{
private:
	//Model* m_graphicalEffects[3];
	ChainEffect* m_chainEffect;
	ParticleEngine* pe[3];
	float m_lifetime;
	Entity* m_eOrig;
	Entity* m_eTarget;
	unsigned int m_lastTarget;
	unsigned int m_target;
	FLOAT3 m_superPos;
	float m_percentToTarget;
	D3DXVECTOR3 m_orig;
public:
	ChainStrikeClientSkillEffect(unsigned int _lastTarget, unsigned int _target, FLOAT3 _position);
	~ChainStrikeClientSkillEffect();

	void update(float _dt);
	bool getActive();
};