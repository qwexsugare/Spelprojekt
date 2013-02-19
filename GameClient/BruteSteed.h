#pragma once
#include "Enemy.h"
#include "Path.h"

class BruteSteed :
	public Enemy
{
public:
	BruteSteed(FLOAT3 _pos, Path _path);
	~BruteSteed(void);

	void attackHero(int heroIndex);
};

