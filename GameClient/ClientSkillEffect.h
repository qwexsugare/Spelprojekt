#pragma once

#include "Entity.h"
#include "DataStructures.h"

class ClientSkillEffect
{
public:
	ClientSkillEffect();
	virtual ~ClientSkillEffect();

	virtual void update(float _dt) = 0;
	virtual bool getActive() = 0;
};