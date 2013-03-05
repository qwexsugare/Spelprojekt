#pragma once

#include "hero.h"
#include "MeleeAOEAttack.h"

class RedKnight : public Hero
{
public:
	RedKnight(int _playerId, WEAPON_TYPE _weaponType);
	~RedKnight();

	int getSubType()const;
};

