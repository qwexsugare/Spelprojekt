#pragma once

#include "Skill.h"

class SwiftAsACatPowerfulAsABoar : public Skill
{
private:
	static const float COOLDOWN;
	int m_master;
public:
	SwiftAsACatPowerfulAsABoar();
	~SwiftAsACatPowerfulAsABoar();

	bool activate(unsigned int _senderId);
	void updateSpecificSkill(float dt);
};

