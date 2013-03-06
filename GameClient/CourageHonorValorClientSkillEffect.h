#pragma once

#include "clientskilleffect.h"
#include "Model.h"

class CourageHonorValorClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_masterId;
	Model* m_model;
	float m_lifetime;
public:
	CourageHonorValorClientSkillEffect(unsigned int _masterId);
	~CourageHonorValorClientSkillEffect();

	bool getActive();
	int getMasterId()const { return m_masterId; }
	void update(float _dt);
};