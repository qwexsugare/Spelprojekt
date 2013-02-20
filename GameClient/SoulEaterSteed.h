#pragma once
#include "Enemy.h"
#include "Path.h"

class SoulEaterSteed :
	public Enemy
{
public:
	SoulEaterSteed(FLOAT3 _pos, Path _path);
	~SoulEaterSteed(void);

	void attackHero(int heroIndex);
};

