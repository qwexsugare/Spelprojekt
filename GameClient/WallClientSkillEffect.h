#pragma once

#include "clientskilleffect.h"
#include "ClientEntityHandler.h"

class WallClientSkillEffect : public ClientSkillEffect
{
private:
	float m_lifetime;

public:
	WallClientSkillEffect(unsigned int _masterId, FLOAT3 _position);
	~WallClientSkillEffect();

	void update(float _dt);
	bool getActive();
};

