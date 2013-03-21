#pragma once

#include "clientskilleffect.h"
#include "Model.h"

class DeathPulseTurretClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_masterId;
	unsigned int m_turretId;
	//Model* m_model;
	float m_timer;
	bool m_active;
	ParticleEngine* m_partOne;
	ParticleEngine* m_partTwo;
public:
	static const int DURATION = 2;

	DeathPulseTurretClientSkillEffect(unsigned int _masterId, unsigned int _targetId);
	~DeathPulseTurretClientSkillEffect();

	bool getActive();
	int getMasterId()const { return m_masterId; }
	void update(float _dt);
};