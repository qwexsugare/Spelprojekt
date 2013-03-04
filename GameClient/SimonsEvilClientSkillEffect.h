#pragma once

#include "clientskilleffect.h"
#include "Model.h"

class SimonsEvilClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_masterId;
	Model* m_model;
	int m_sound;
	float m_timer;
public:
	SimonsEvilClientSkillEffect(unsigned int _masterId);
	~SimonsEvilClientSkillEffect();

	bool getActive();
	int getMasterId()const { return m_masterId; }
	void update(float _dt);
};