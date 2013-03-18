#pragma once

#include "ServerEntity.h"
#include "Skill.h"

class EnigmaticPresenceEffect : public ServerEntity
{
private:
	map<unsigned int, float> m_affectedGuys;
	unsigned int m_caster;
public:
	static const float MOVEMENT_SPEED_FACTOR;
	static const int AOE = 10;

	EnigmaticPresenceEffect(unsigned int _caster);
	~EnigmaticPresenceEffect();

	void update(float _dt);
};