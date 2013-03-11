#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"
#include "PointLight.h"
#include "ClientEntityHandler.h"

class ChainStrikeClientSkillEffect : public ClientSkillEffect
{
private:
	Model* m_graphicalEffects[3];
	float m_lifetime;
public:
	ChainStrikeClientSkillEffect(unsigned int _lastTarget, unsigned int _target, FLOAT3 _position);
	~ChainStrikeClientSkillEffect();

	void update(float _dt);
	bool getActive();
};