#pragma once

#include "clientskilleffect.h"
#include "ClientEntityHandler.h"

class DeathClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_masterId;
	Model *m_model;
	float m_lifetime;
	bool m_sink;
public:
	DeathClientSkillEffect(unsigned int _masterId, FLOAT3 _position);
	~DeathClientSkillEffect();

	void update(float dt);
	bool getActive();
};

