#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"
#include "PointLight.h"
#include "ClientEntityHandler.h"

class ChainStrikeClientSkillEffect : public ClientSkillEffect
{
private:
	Model* m_graphicalEffects[3];
	int m_sound;
	float m_lifetime;
public:
	ChainStrikeClientSkillEffect(unsigned int _masterId, FLOAT3 _position, bool _playAnimation);
	~ChainStrikeClientSkillEffect();

	void update(float _dt);
	bool getActive();
};