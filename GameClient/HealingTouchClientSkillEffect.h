#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"
#include "ClientEntityHandler.h"

class HealingTouchClientSkillEffect : public ClientSkillEffect
{
private:
	FLOAT3 m_position;
	float m_lifetime;
	Mesh* m_weapon;
	UINT m_casterId;
	UINT m_targetId;
	ParticleEngine* m_heal;
public:
	HealingTouchClientSkillEffect(FLOAT3 _position, unsigned int casterId, unsigned int _targetId);
	~HealingTouchClientSkillEffect();

	void update(float _dt);
	bool getActive();
};