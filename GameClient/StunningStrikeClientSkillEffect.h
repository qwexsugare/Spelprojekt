#pragma once

#include "ClientSkillEffect.h"
#include "PointLight.h"

class StunningStrikeClientSkillEffect : public ClientSkillEffect
{
private:
	PointLight* m_graphicalEffect;
	int m_sound;
	FLOAT3 m_position;
	float m_lifetime;
public:
	StunningStrikeClientSkillEffect(FLOAT3 _position);
	~StunningStrikeClientSkillEffect();

	void update(float _dt);
	bool getActive();
};