#pragma once
#include "Enemy.h"

class Shade :
	public Enemy
{
public:
	Shade(FLOAT3 _pos, Path _path);
	~Shade(void);

	void attackHero(int heroIndex);
};

