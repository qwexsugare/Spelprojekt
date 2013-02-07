#pragma once

#include "ServerEntity.h"
#include "Skill.h"

class DemonicPresenceEffect
 : public ServerEntity
{
private:
	static vector<unsigned int> m_affectedGuys;
	float m_timer;
	unsigned int m_caster;

	static const int AOE = 10;
	static const float MOVEMENT_SPEED_BOOST;
	static const float ATTACK_SPEED_BOOST;
public:
	static const int LIFETIME = 3;

	DemonicPresenceEffect(unsigned int _caster);
	~DemonicPresenceEffect();

	void update(float _dt);
};