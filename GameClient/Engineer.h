#pragma once

#include "hero.h"

class Engineer : public Hero
{
public:
	Engineer(int _playerId, WEAPON_TYPE _weaponType);
	~Engineer();

	int getSubType()const;
};

