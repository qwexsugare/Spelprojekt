#pragma once

#include "ServerEntity.h"
#include "Skill.h"

struct AffectedGuy
{
	unsigned int id;
	float mentalResistanceChange;
	float movementChange;
	int mentalDamageChange;

	AffectedGuy(unsigned int _id, float _mentalResistanceChange, float _movementChange, int _mentalDamageChange)
	{
		id = _id;
		mentalResistanceChange = _mentalResistanceChange;
		movementChange = _movementChange;
		mentalDamageChange = _mentalDamageChange;
	}
};

class CourageHonorValorEffect : public ServerEntity
{
private:
	vector<AffectedGuy> m_affectedGuys;
	float m_timer;
	unsigned int m_caster;
public:
	static const float MOVEMENT_SPEED_BASE;
	static const float MOVEMENT_SPEED_FACTOR;
	static const float MENTAL_RESISTANCE_FACTOR;
	static const float MENTAL_RESISTANCE_BASE;
	static const float MENTAL_DAMAGE_FACTOR;
	static const float MENTAL_DAMAGE_BASE;
	static const int AOE = 10;

	CourageHonorValorEffect(unsigned int _caster);
	~CourageHonorValorEffect();

	void update(float _dt);
};