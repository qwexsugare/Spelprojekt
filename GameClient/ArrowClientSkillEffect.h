#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"
#include "Hero.h"

class ArrowClientSkillEffect : public ClientSkillEffect
{
private:
	Model* m_graphicalEffect;
	unsigned int m_targetId;
	bool m_active;
public:
	ArrowClientSkillEffect(FLOAT3 _position, unsigned int _targetId, unsigned int _masterId);
	~ArrowClientSkillEffect();

	void update(float _dt);
	bool getActive();
};