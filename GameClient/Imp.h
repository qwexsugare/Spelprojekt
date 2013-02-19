#pragma once
#include "enemy.h"
#include "Path.h"
class Imp :
	public Enemy
{
public:
	Imp(FLOAT3 _pos, Path _path);
	~Imp(void);

	void attackHero(int heroIndex);
};

