#pragma once
#include "clientskilleffect.h"
class TargetAcquiredClientSkillEffect : public ClientSkillEffect
{
private:
	float m_lifetime;
	Model *m_model;
public:
	TargetAcquiredClientSkillEffect(unsigned int _masterId, FLOAT3 position);
	~TargetAcquiredClientSkillEffect();

	void update(float _dt);
	bool getActive();
};

