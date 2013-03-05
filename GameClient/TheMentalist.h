#pragma once

#include "hero.h"

class TheMentalist : public Hero
{
public:
	TheMentalist(int _playerId, WEAPON_TYPE _weaponType);
	~TheMentalist();

	int getSubType()const;
};

