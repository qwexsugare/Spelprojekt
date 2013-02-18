#pragma once

#include "Skill.h"

class CourageHonorValor : public Skill
{
public:
	static const int COST = 4000;

	CourageHonorValor();
	~CourageHonorValor();

	virtual bool activate(unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};