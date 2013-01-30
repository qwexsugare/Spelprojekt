#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"

class HealingTouchClientSkillEffect : public ClientSkillEffect
{
private:
	Model* m_graphicalEffect;
	int m_sound;
	FLOAT3 m_position;
	float m_lifetime;
public:
	HealingTouchClientSkillEffect(FLOAT3 _position);
	~HealingTouchClientSkillEffect();

	void update(float _dt);
	bool getActive();
};