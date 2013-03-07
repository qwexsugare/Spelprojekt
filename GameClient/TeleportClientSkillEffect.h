#pragma once

#include "clientskilleffect.h"
#include "Model.h"

class TeleportClientSkillEffect : public ClientSkillEffect
{
public:
	TeleportClientSkillEffect(const FLOAT3& _position);
	~TeleportClientSkillEffect();

	bool getActive();
	void update(float _dt);
};