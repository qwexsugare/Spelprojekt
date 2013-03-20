#pragma once

#include "clientskilleffect.h"
#include "Model.h"

class DeathPulseTurretClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_masterId;
	Model* m_model;
	int m_sound;
	//float m_soundVolume;
	float m_timer;
	bool m_active;
public:
	static const int DURATION = 2;

	DeathPulseTurretClientSkillEffect(unsigned int _masterId);
	~DeathPulseTurretClientSkillEffect();

	bool getActive();
	int getMasterId()const { return m_masterId; }
	void update(float _dt);
};