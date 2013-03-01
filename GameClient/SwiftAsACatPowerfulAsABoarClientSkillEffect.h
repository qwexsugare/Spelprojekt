#pragma once

#include "clientskilleffect.h"
#include "ClientEntityHandler.h"

class SwiftAsACatPowerfulAsABoarClientSkillEffect : public ClientSkillEffect
{
public:
	SwiftAsACatPowerfulAsABoarClientSkillEffect(unsigned int _masterId);
	~SwiftAsACatPowerfulAsABoarClientSkillEffect();

	void update(float _dt);
	bool getActive();
};

