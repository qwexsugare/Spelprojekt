#pragma once
#include "Enemy.h"
#include "Path.h"

class SpittingDemon :
	public Enemy
{
public:
	SpittingDemon(FLOAT3 _pos, Path _path);
	~SpittingDemon(void);

	void attackHero(int heroIndex);
};

