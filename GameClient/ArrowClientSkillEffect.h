#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"

class ArrowClientSkillEffect : public ClientSkillEffect
{
private:
	Model* m_graphicalEffect;
	int m_sound;
	unsigned int m_targetId;
	bool m_active;
	bool m_unitTookDamage;
public:
	ArrowClientSkillEffect(FLOAT3 _position, unsigned int _targedId, unsigned int _masterId);
	~ArrowClientSkillEffect();

	unsigned int getTargetId()const;
	bool unitTookDamage()const;
	void update(float _dt);
	bool getActive();
};