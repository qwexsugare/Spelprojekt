#pragma once
#include "Enemy.h"
#include "Path.h"

class ThunderSteed :
	public Enemy
{
public:
	ThunderSteed(FLOAT3 _pos, Path _path);
	~ThunderSteed(void);

	void attackHero(int heroIndex);
};

