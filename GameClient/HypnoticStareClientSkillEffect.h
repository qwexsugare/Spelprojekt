#pragma once

#include "clientskilleffect.h"
#include "Model.h"

class HypnoticStareClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_casterId;
	unsigned int m_masterId;
	float m_timer;
	string m_oldTexture;
	string m_oldGlow;
	bool m_active;
public:
	HypnoticStareClientSkillEffect(unsigned int _masterId, unsigned int _casterId, float _duration);
	~HypnoticStareClientSkillEffect();

	bool getActive();
	int getMasterId()const { return m_masterId; }
	void update(float _dt);
};