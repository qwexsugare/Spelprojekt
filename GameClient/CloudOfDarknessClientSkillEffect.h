#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"
#include "PointLight.h"
#include "ClientEntityHandler.h"

class CloudOfDarknessClientSkillEffect : public ClientSkillEffect
{
private:
	Model* m_graphicalEffects[3];
	PointLight* m_light;
	FLOAT3 m_position;
	float m_lifetime;
	ParticleEngine* m_cloud;
	Mesh* m_weapon;
	UINT m_masterId;
public:
	CloudOfDarknessClientSkillEffect(unsigned int _masterId, FLOAT3 _position);
	~CloudOfDarknessClientSkillEffect();

	void update(float _dt);
	bool getActive();
};