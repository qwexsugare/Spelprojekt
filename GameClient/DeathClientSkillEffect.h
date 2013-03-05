#pragma once

#include "clientskilleffect.h"
#include "ClientEntityHandler.h"

class DeathClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_masterId;
	Model *m_model;
	PointLight *m_lanternLight;
	FLOAT3 m_originalDiffuse;
	FLOAT3 m_originalSpecular;
	float m_lifetime;
	bool m_sink;
public:
	DeathClientSkillEffect(unsigned int _masterId, FLOAT3 _position);
	~DeathClientSkillEffect();

	void update(float dt);
	bool getActive();
};

