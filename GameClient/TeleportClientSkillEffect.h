#pragma once

#include "clientskilleffect.h"
#include "Model.h"

class TeleportClientSkillEffect : public ClientSkillEffect
{
private:
	unsigned int m_casterId;
	FLOAT3 m_position;
public:
	TeleportClientSkillEffect(unsigned int _casterId, const FLOAT3& _position);
	~TeleportClientSkillEffect();

	bool getActive();
	void update(float _dt);
};