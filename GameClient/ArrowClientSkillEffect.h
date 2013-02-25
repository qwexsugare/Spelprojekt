#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"
#include "Hero.h"

class ArrowClientSkillEffect : public ClientSkillEffect
{
private:
	Model* m_graphicalEffect;
	int m_sound;
	unsigned int m_targetId;
	bool m_active;
	Hero::HERO_TYPE m_heroType;
public:
	ArrowClientSkillEffect(FLOAT3 _position, unsigned int _targetId, unsigned int _masterId);
	ArrowClientSkillEffect(FLOAT3 _position, unsigned int _targetId, Hero::HERO_TYPE _heroType);
	~ArrowClientSkillEffect();

	void update(float _dt);
	bool getActive();
};