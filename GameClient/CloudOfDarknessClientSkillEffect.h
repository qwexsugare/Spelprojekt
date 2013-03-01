#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"
#include "PointLight.h"

class CloudOfDarknessClientSkillEffect : public ClientSkillEffect
{
private:
	Model* m_graphicalEffects[3];
	PointLight* m_light;
	int m_sound;
	FLOAT3 m_position;
	float m_lifetime;
	ParticleEngine* particleSystem;
public:
	CloudOfDarknessClientSkillEffect(FLOAT3 _position);
	~CloudOfDarknessClientSkillEffect();

	void update(float _dt);
	bool getActive();
};