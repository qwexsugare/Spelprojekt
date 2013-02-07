#pragma once

#include "clientskilleffect.h"
#include "Model.h"

class DemonicPresenceClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_masterId;
	Model* m_model;
public:
	DemonicPresenceClientSkillEffect(unsigned int _masterId);
	~DemonicPresenceClientSkillEffect();

	bool getActive();
	int getMasterId()const { return m_masterId; }
	void update(float _dt);
};