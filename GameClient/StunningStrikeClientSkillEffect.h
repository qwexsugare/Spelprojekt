#pragma once

#include "ClientSkillEffect.h"
#include "PointLight.h"
#include "ClientEntityHandler.h"

class StunningStrikeClientSkillEffect : public ClientSkillEffect
{
private:
	int m_sound;
	FLOAT3 m_position;
	float m_lifetime;
public:
	StunningStrikeClientSkillEffect(unsigned int _masterId, FLOAT3 _position);
	~StunningStrikeClientSkillEffect();

	void update(float _dt);
	bool getActive();
};