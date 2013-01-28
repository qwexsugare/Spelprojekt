#pragma once

#include "ClientSkillEffect.h"

class CloudOfDarknessClientSkillEffect : public ClientSkillEffect
{
private:
	int m_sound;
	FLOAT3 m_position;
	float m_lifetime;
public:
	CloudOfDarknessClientSkillEffect(FLOAT3 _position);
	~CloudOfDarknessClientSkillEffect();

	void update(float _dt);
	bool getActive();
};