#pragma once
#include "Enemy.h"
#include "Path.h"

class HellfireSteed :
	public Enemy
{
public:
	HellfireSteed(FLOAT3 _pos, Path _path);
	~HellfireSteed(void);

	void attackHero(int heroIndex);
};

