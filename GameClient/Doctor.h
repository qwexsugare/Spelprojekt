#pragma once

#include "hero.h"

class Doctor : public Hero
{
public:
	Doctor(int _playerId, WEAPON_TYPE _weaponType);
	~Doctor();
};

