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
public:
	ArrowClientSkillEffect(FLOAT3 _position, unsigned int _targedId);
	~ArrowClientSkillEffect();

	void update(float _dt);
	bool getActive();
};