#pragma once

#include "hero.h"

class Officer : public Hero
{
public:
	Officer(int _playerId, WEAPON_TYPE _weaponType);
	~Officer();

	int getSubType()const;
};

