#pragma once

#include "clientskilleffect.h"

class ChurchPenetratedClientSkillEffect : public ClientSkillEffect
{
public:
	ChurchPenetratedClientSkillEffect(unsigned int _id, FLOAT3 _position);
	~ChurchPenetratedClientSkillEffect(void);

	void update(float _dt);
	bool getActive();
};

